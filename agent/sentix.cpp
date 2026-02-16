#include <iostream>
#include <fstream>  // Untuk baca file (ifstream)
#include <string>   // Untuk manipulasi teks
#include <cstdlib>  // Untuk fungsi system()
#include <unistd.h> // Untuk fungsi sleep()

using namespace std;

int main() {
    cout << "[SENTIX DAEMON] Starting memory surveillance..." << endl;

    // The Infinite Loop (Ouroboros)
    while (true) {
        long memTotal = 0;
        long memAvailable = 0;

        // TUGAS 1: Buka file /proc/meminfo
        // Hint: Gunakan std::ifstream
        std::ifstream meminfo("/proc/meminfo");

        // TUGAS 2: Baca file baris per baris
        // Hint: Gunakan perulangan while dan getline().
        // Kalau ketemu kata "MemTotal:", simpan angkanya ke variabel memTotal.
        // Kalau ketemu kata "MemAvailable:", simpan angkanya ke variabel memAvailable.
        std::string line;
        while (std::getline(meminfo, line)){
            if (line.find("MemTotal:") != std::string::npos){
                memTotal = std::stol(line.substr(line.find(":") + 1));
            } else if (line.find("MemAvailable:") != std::string::npos){
                memAvailable = std::stol(line.substr(line.find(":") + 1));
            }
        }

        // TUGAS 3: Hitung Persentase RAM Terpakai
        // Rumus: ((Total - Available) / Total) * 100
        // Hint MatDis: Hati-hati pembagian integer (long) di C++ bisa jadi 0!
        // Pastikan di-cast ke float/double dulu pas ngitung persentase.
        double ramUsagePercent = 0.0; // Ganti dengan hasil hitunganmu
        ramUsagePercent = ((memTotal - memAvailable) / static_cast<double>(memTotal)) * 100;

        cout << "Current RAM Usage: " << ramUsagePercent << "%" << endl;

        // TUGAS 4: Logika Eksekusi (The Trigger)
        // Jika ramUsagePercent > 90.0, maka panggil script heal.sh
        // Hint: Gunakan fungsi system() untuk menjalankan perintah terminal dari C++
        if (ramUsagePercent > 90.0){
            system("bash /home/yui/Dev/Kuliah/sentix-daemon/agent/actions/heal.sh");
        }

        // Tidur selama 3 detik sebelum ngecek lagi biar CPU nggak meledak
        sleep(3);
    }

    return 0;
}
