#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/packet-sink.h"
#include <fstream>
#include <string>
#include <cmath>  // Para cálculos teóricos

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("MM1KQueue");

class QueueMonitor : public Object
{
public:
  static TypeId GetTypeId (void)
  {
    static TypeId tid = TypeId ("ns3::QueueMonitor")
      .SetParent<Object> ()
      .SetGroupName ("Queue")
      .AddConstructor<QueueMonitor> ();
    return tid;
  }

  QueueMonitor ()
    : m_nPackets (0),
      m_nDropped (0),
      m_nReceived (0),
      m_deliveryRatio (0),
      m_avgQueueSize (0)
  {
    m_fstream.open ("queue-stats.txt", std::ios::out);
  }

  ~QueueMonitor ()
  {
    m_fstream.close ();
  }

  void
  PacketEnqueue (Ptr<const Packet> packet)
  {
    m_nPackets++;
    m_queueSize++;
    m_avgQueueSize = ((m_avgQueueSize * (m_nPackets - 1)) + m_queueSize) / m_nPackets;
    
    LogStats ();
  }

  void
  PacketDequeue (Ptr<const Packet> packet)
  {
    m_queueSize--;
    m_nReceived++;
    m_deliveryRatio = static_cast<double> (m_nReceived) / m_nPackets;
    
    LogStats ();
  }

  void
  PacketDrop (Ptr<const Packet> packet)
  {
    m_nDropped++;
    LogStats ();
  }

  // Obtener valores simulados para la comparación
  uint32_t GetPacketsReceived () const { return m_nReceived; }
  uint32_t GetPacketsDropped () const { return m_nDropped; }
  double GetAvgQueueSize () const { return m_avgQueueSize; }
  double GetDeliveryRatio () const { return m_deliveryRatio; }

private:
  void
  LogStats ()
  {
    if (m_fstream.is_open ())
      {
        m_fstream << Simulator::Now ().GetSeconds () << "\t"
                 << m_queueSize << "\t"
                 << m_nPackets << "\t"
                 << m_nDropped << "\t"
                 << m_nReceived << "\t"
                 << m_deliveryRatio << "\t"
                 << m_avgQueueSize << std::endl;
      }
  }

  uint32_t m_nPackets;
  uint32_t m_nDropped;
  uint32_t m_nReceived;
  uint32_t m_queueSize;
  double m_deliveryRatio;
  double m_avgQueueSize;
  std::ofstream m_fstream;
};

int
main (int argc, char *argv[])
{
  // Configuración de parámetros de simulación
  double simTime = 100.0;
  uint32_t queueSize = 10;
  double lambda = 2.0;
  double mu = 4.0;
  uint32_t packetSize = 1024;

  CommandLine cmd (_FILE_);
  cmd.AddValue ("simTime", "Tiempo de simulación (s)", simTime);
  cmd.AddValue ("queueSize", "Tamaño de la cola (packets)", queueSize);
  cmd.AddValue ("lambda", "Tasa de llegada (packets/s)", lambda);
  cmd.AddValue ("mu", "Tasa de servicio (packets/s)", mu);
  cmd.Parse (argc, argv);

  // Configurar logging
  LogComponentEnable ("MM1KQueue", LOG_LEVEL_INFO);

  // Crear nodos
  NodeContainer nodes;
  nodes.Create (2);

  // Configurar enlace punto a punto
  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue (std::to_string (mu * packetSize * 8) + "bps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));
  
  // Configurar cola
  pointToPoint.SetQueue ("ns3::DropTailQueue",
                        "MaxSize", StringValue (std::to_string (queueSize) + "p"));

  NetDeviceContainer devices;
  devices = pointToPoint.Install (nodes);

  // Instalar pila de Internet
  InternetStackHelper stack;
  stack.Install (nodes);

  // Asignar direcciones IP
  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces = address.Assign (devices);

  // Crear y configurar monitor de cola
  Ptr<QueueMonitor> monitor = CreateObject<QueueMonitor> ();

  // Configurar aplicaciones
  uint16_t port = 9;

  // Aplicación emisora (OnOff)
  OnOffHelper onOff ("ns3::UdpSocketFactory",
                    Address (InetSocketAddress (interfaces.GetAddress (1), port)));
  
  // Configurar tasa de envío
  onOff.SetConstantRate (DataRate (lambda * packetSize * 8));
  onOff.SetAttribute ("PacketSize", UintegerValue (packetSize));
  
  // Instalar aplicación emisora
  ApplicationContainer apps = onOff.Install (nodes.Get (0));
  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (simTime));

  // Aplicación receptora (PacketSink)
  PacketSinkHelper sink ("ns3::UdpSocketFactory",
                        Address (InetSocketAddress (Ipv4Address::GetAny (), port)));
  apps = sink.Install (nodes.Get (1));
  apps.Start (Seconds (0.0));
  apps.Stop (Seconds (simTime + 0.1));

  // Conectar trazas para monitoreo
  Config::ConnectWithoutContext ("/NodeList/0/DeviceList/*/TxQueue/Enqueue",
                                MakeCallback (&QueueMonitor::PacketEnqueue, monitor));
  Config::ConnectWithoutContext ("/NodeList/0/DeviceList/*/TxQueue/Dequeue",
                                MakeCallback (&QueueMonitor::PacketDequeue, monitor));
  Config::ConnectWithoutContext ("/NodeList/0/DeviceList/*/TxQueue/Drop",
                                MakeCallback (&QueueMonitor::PacketDrop, monitor));

  // Configurar FlowMonitor
  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor_flow = flowmon.InstallAll ();

  // Ejecutar simulación
  Simulator::Stop (Seconds (simTime + 0.1));
  Simulator::Run ();

  // Recolectar estadísticas
  monitor_flow->CheckForLostPackets ();
  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  std::map<FlowId, FlowMonitor::FlowStats> stats = monitor_flow->GetFlowStats ();

  // Cálculos teóricos
  double rho = lambda / mu;
  double Ns, Nq, Ts, Tq;

  // Fórmulas para M/M/1/K
  Ns = rho / (1 - rho); // Número promedio de clientes en el sistema
  Nq = rho * rho / (1 - rho); // Número promedio de clientes en cola
  Ts = Ns / lambda; // Tiempo promedio en el sistema
  Tq = Nq / lambda; // Tiempo promedio en cola

  // Imprimir resultados teóricos
  std::cout << "\n--- Resultados Teóricos ---\n";
  std::cout << "Número promedio de clientes en el sistema (Ns): " << Ns << "\n";
  std::cout << "Número promedio de clientes en la cola (Nq): " << Nq << "\n";
  std::cout << "Tiempo promedio en el sistema (Ts): " << Ts << " s\n";
  std::cout << "Tiempo promedio en la cola (Tq): " << Tq << " s\n";

  // Imprimir estadísticas simuladas
  std::cout << "\n--- Resultados Simulados ---\n";
  std::cout << "Paquetes recibidos: " << monitor->GetPacketsReceived () << "\n";
  std::cout << "Paquetes perdidos: " << monitor->GetPacketsDropped () << "\n";
  std::cout << "Tamaño promedio de la cola: " << monitor->GetAvgQueueSize () << "\n";
  std::cout << "Ratio de entrega: " << monitor->GetDeliveryRatio () << "\n";

  Simulator::Destroy ();
  return 0;
}