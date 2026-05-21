#define NETWORKMONITOR_EXPORTS

#include "NetworkMonitor.hpp"

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>
#include <limits>

#include <arpa/inet.h>
#include "PcapLiveDeviceList.h"
#include "PcapLiveDevice.h"
#include "Packet.h"
#include "IPv4Layer.h"
#include "TcpLayer.h"
#include "UdpLayer.h"

/*
===================================================
Hacemos la parte del loggs
===================================================
*/


using namespace pcpp;

namespace
{


    enum class LogLevel
    {
        Info,
        Warning,
        Error
    };

    void log(LogLevel level, const std::string& message)
    {
        std::string prefix;

        switch (level)
        {
            case LogLevel::Info:
                prefix = "[INFO]";
                break;

            case LogLevel::Warning:
                prefix = "[WARNING]";
                break;

            case LogLevel::Error:
                prefix = "[ERROR]";
                break;
        }

        std::cout
            << prefix
            << " "
            << message
            << std::endl;
    }

    /*
        ===================================================
        Estructuras del logger
        ===================================================
    */

    struct Alert
    {
        std::string ip;
        std::string reason;
        std::string timestamp;
    };

    struct TrafficStats
    {
        uint64_t totalPackets = 0;
        uint64_t totalBytes = 0;

        uint64_t tcpPackets = 0;
        uint64_t udpPackets = 0;

        uint64_t suspiciousEvents = 0;

        std::unordered_map<uint16_t, uint64_t> ports;
    };



    std::unordered_map<std::string, TrafficStats> g_stats;

    std::vector<Alert> g_alerts;

    /*
        ===================================================
        Usamos Mutex para buena medida al estar usando synhro o psoibles hilos para evitar  problemas
        ===================================================
    */

    std::mutex g_mutex;


    std::string getTimestamp()
    {
        auto now =
            std::chrono::system_clock::now();

        auto nowTime =
            std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;

        ss << std::put_time(
            std::localtime(&nowTime),
            "%Y-%m-%d %H:%M:%S"
        );

        return ss.str();
    }

    void createAlert(
        const std::string& ip,
        const std::string& reason)
    {
        Alert alert;

        alert.ip = ip;
        alert.reason = reason;
        alert.timestamp = getTimestamp();

        g_alerts.push_back(alert);

        log(
            LogLevel::Warning,
            ip + " -> " + reason
        );
    }

    /*
        ===================================================
        Primero se analiza cuato se lee puertos o puertos sensibles como forma 
        ===================================================
    */

    void analyzeTraffic(
        const std::string& ip,
        uint16_t port,
        TrafficStats& stats)
    {
        constexpr size_t PORT_SCAN_THRESHOLD = 25;

        if (stats.ports.size() > PORT_SCAN_THRESHOLD)
        {
            stats.suspiciousEvents++;

            createAlert(
                ip,
                "Posible port scanning"
            );
        }

        const std::vector<uint16_t> sensitivePorts =
        {
            22,
            23,
            445,
            3389
        };

        for (uint16_t sensitivePort : sensitivePorts)
        {
            auto it =
                stats.ports.find(sensitivePort);

            if (it == stats.ports.end())
            {
                continue;
            }

            if (it->second > 100)
            {
                stats.suspiciousEvents++;

                createAlert(
                    ip,
                    "Actividad sospechosa en puerto sensible: "
                    + std::to_string(sensitivePort)
                );
            }
        }
    }

    /*
        ===================================================
        Tomar el paquete lo proesa y "desempaquetarlo" para su uso del analisis
        ===================================================
    */

    void onPacketArrives(
        RawPacket* rawPacket,
        PcapLiveDevice*,
        void*)
    {
        try
        {
            Packet packet(rawPacket);

            IPv4Layer* ipLayer =
                packet.getLayerOfType<IPv4Layer>();

            if (ipLayer == nullptr)
            {
                return;
            }

            std::string srcIp =
                ipLayer->getSrcIPAddress().toString();

            std::lock_guard<std::mutex> lock(g_mutex);

            auto& stats = g_stats[srcIp];

            stats.totalPackets++;

            stats.totalBytes +=
                rawPacket->getRawDataLen();

            /*
                TCP
            */

            if (packet.isPacketOfType(TCP))
            {
                TcpLayer* tcpLayer =
                    packet.getLayerOfType<TcpLayer>();

                if (tcpLayer != nullptr)
                {
                    stats.tcpPackets++;

                    uint16_t dstPort =
                        ntohs(
                            tcpLayer
                            ->getTcpHeader()
                            ->portDst
                        );

                    stats.ports[dstPort]++;

                    analyzeTraffic(
                        srcIp,
                        dstPort,
                        stats
                    );
                }
            }

            /*
                UDP
            */

            if (packet.isPacketOfType(UDP))
            {
                stats.udpPackets++;
            }


            constexpr uint64_t TRAFFIC_THRESHOLD = 5000;

            if (stats.totalPackets > TRAFFIC_THRESHOLD)
            {
                createAlert(
                    srcIp,
                    "Exceso de tráfico"
                );
            }
        }
        catch (const std::exception& ex)
        {
            log(LogLevel::Error, ex.what());
        }
    }

    /*
        ===================================================
        REPORTE
        ===================================================
    */

    void generateReport()
    {
        std::ofstream report("network_report.txt");

        if (!report.is_open())
        {
            log(
                LogLevel::Error,
                "No se pudo crear el reporte."
            );

            return;
        }

        report << "=================================\n";
        report << " NETWORK ANALYSIS REPORT\n";
        report << "=================================\n\n";

        for (const auto& [ip, stats] : g_stats)
        {
            report << "IP: " << ip << "\n";

            report << "  Total Packets: "
                   << stats.totalPackets << "\n";

            report << "  Total Bytes: "
                   << stats.totalBytes << "\n";

            report << "  TCP Packets: "
                   << stats.tcpPackets << "\n";

            report << "  UDP Packets: "
                   << stats.udpPackets << "\n";

            report << "  Suspicious Events: "
                   << stats.suspiciousEvents << "\n";

            report << "\n";
        }

        report << "=================================\n";
        report << " ALERTS\n";
        report << "=================================\n\n";

        for (const auto& alert : g_alerts)
        {
            report
                << "["
                << alert.timestamp
                << "] "
                << alert.ip
                << " -> "
                << alert.reason
                << "\n";
        }

        report.close();

        log(
            LogLevel::Info,
            "Reporte generado: network_report.txt"
        );
    }
}

/*
    ==========================================================
    Busqueda de las interfaces para el analisis
    ==========================================================
*/

namespace NetMon
{
    void NetworkMonitor::run()
    {
        /*
            Obtener interfaces
        */

        const auto& devices =
            PcapLiveDeviceList::getInstance()
            .getPcapLiveDevicesList();

        if (devices.empty())
        {
            log(
                LogLevel::Error,
                "No se encontraron interfaces."
            );

            return;
        }

        /*
            Mostrar interfaces
        */

        std::cout << "\n====================================\n";
        std::cout << " INTERFACES DISPONIBLES\n";
        std::cout << "====================================\n\n";

        for (size_t i = 0; i < devices.size(); ++i)
        {
            std::cout
                << "[" << i << "] "
                << devices[i]->getDesc()
                << std::endl;

            std::cout
                << "    "
                << devices[i]->getName()
                << std::endl;

            std::cout
                << "------------------------------------"
                << std::endl;
        }

        /*
            Selección
        */

        int selectedIndex = -1;

        while (true)
        {
            std::cout
                << "\nSelecciona una interfaz: ";

            std::cin >> selectedIndex;

            if (std::cin.fail())
            {
                std::cin.clear();

                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(),
                    '\n'
                );

                std::cout
                    << "Entrada inválida."
                    << std::endl;

                continue;
            }

            if (selectedIndex < 0 ||
                selectedIndex >= static_cast<int>(devices.size()))
            {
                std::cout
                    << "Índice inválido."
                    << std::endl;

                continue;
            }

            break;
        }

        /*
            Tiempo captura
        */

        int captureTime = 30;

        std::cout
            << "\nTiempo de captura (segundos): ";

        std::cin >> captureTime;

        if (std::cin.fail() || captureTime <= 0)
        {
            captureTime = 30;
        }

        /*
            Abrir interfaz
        */

        PcapLiveDevice* device =
            devices[selectedIndex];

        if (!device->open())
        {
            log(
                LogLevel::Error,
                "No se pudo abrir la interfaz."
            );

            return;
        }

        /*
            Iniciar captura
        */

        log(
            LogLevel::Info,
            "Iniciando captura..."
        );

        if (!device->startCapture(
            onPacketArrives,
            nullptr))
        {
            log(
                LogLevel::Error,
                "Error iniciando captura."
            );

            device->close();

            return;
        }

        /*
            Esperar
        */

        std::this_thread::sleep_for(
            std::chrono::seconds(captureTime)
        );

        /*
            Finalizar
        */

        device->stopCapture();

        device->close();

        log(
            LogLevel::Info,
            "Captura finalizada."
        );

        /*
            Reporte
        */

        generateReport();
    }
}
