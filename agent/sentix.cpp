#include <iostream>
#include <fstream>  // Untuk baca file (ifstream)
#include <string>   // Untuk manipulasi teks
#include <cstdlib>  // Untuk fungsi system()
#include <unistd.h> // Untuk fungsi sleep()
#include <pqxx/pqxx> // Untuk koneksi database

using namespace std;

int main() {
    cout << "[SENTIX DAEMON] Starting memory surveillance..." << endl;
    std::string connectionString = "dbname=sentix user=sentix password=sentix host=localhost port=5432";

    try{
        pqxx::connection conn(connectionString);
        if (conn.is_open()){
            std::cout << "Database connection successful!" << std::endl;
        } else {
            std::cout << "Database connection failed!" << std::endl;
        }

        // infinite loop
        while (true) {
            long memTotal = 0;
            long memAvailable = 0;
            std::ifstream meminfo("/proc/meminfo");
            std::string line;

            // mencari memTotal dan memAvailable
            while (std::getline(meminfo, line)){
                if (line.find("MemTotal:") != std::string::npos){
                    memTotal = std::stol(line.substr(line.find(":") + 1));
                } else if (line.find("MemAvailable:") != std::string::npos){
                    memAvailable = std::stol(line.substr(line.find(":") + 1));
                }
            }

            // menghitung persentase RAM terpakai
            double ramUsagePercent = 0.0;
            ramUsagePercent = ((memTotal - memAvailable) / static_cast<double>(memTotal)) * 100;

            cout << "Current RAM Usage: " << ramUsagePercent << "%" << endl;

            // kalau ramUsagePercent > 90.0, maka panggil script heal.sh
            if (ramUsagePercent > 90.0){
                system("bash /home/yui/Dev/Kuliah/sentix-daemon/agent/actions/heal.sh");
            }

            // insert data ke database
            try{
                pqxx::work txn(conn);
                txn.exec("INSERT INTO memory_logs (ram_usage_percent) VALUES (" + to_string(ramUsagePercent) + ")");
                txn.commit();
            } catch (const std::exception& e){
                std::cout << "Failed to insert data into database!" << std::endl;
            }

            // Tidur selama 3 detik sebelum ngecek lagi
            sleep(3);
        }

        return 0;

    } catch (const std::exception& e){
        std::cout << "Database connection error: " << e.what() << std::endl;
    }

}
