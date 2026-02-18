# 👁️‍🗨️ Sentix Daemon & Telemetry Dashboard

A bare-metal, lightweight system telemetry agent written in native C++ that performs real-time memory surveillance. It is tightly integrated with a modern Laravel Livewire dashboard to visualize system health metrics via a Dockerized PostgreSQL infrastructure.

![Status](https://img.shields.io/badge/Status-Active_Development-success?style=for-the-badge)
![C++](https://img.shields.io/badge/Agent-C++_Native-00599C?style=for-the-badge&logo=c%2B%2B)
![Laravel](https://img.shields.io/badge/Dashboard-Laravel_11-FF2D20?style=for-the-badge&logo=laravel)
![Docker](https://img.shields.io/badge/Infrastructure-Docker-2496ED?style=for-the-badge&logo=docker)
![PostgreSQL](https://img.shields.io/badge/Database-PostgreSQL-4169E1?style=for-the-badge&logo=postgresql)

---

## ⚙️ Requirements

Pastikan sistem kamu sudah terinstall:

- **Docker & Docker Compose** — Untuk infrastruktur & dashboard
- **G++ Compiler & libpqxx** — Untuk kompilasi agent C++
- **Linux Environment** — Disarankan Arch Linux / Ubuntu / Debian untuk akses `/proc/meminfo`

---

## 🚀 Quick Start

### 1. Persiapan Repository

Clone repository ini dan siapkan file environment:

```bash
git clone https://github.com/USERNAME_KAMU/sentix-daemon.git
cd sentix-daemon
cp .env.example .env
```

> **Catatan:** Jangan lupa edit file `.env` dan isi dengan kredensial database yang aman.

---

### 2. Menjalankan Infrastruktur & Web Dashboard

Inisialisasi container Docker (PostgreSQL & PHP 8.3) dan lakukan migrasi database Laravel.

```bash
# Build dan jalankan container di background
docker compose up -d --build

# Masuk ke dalam container aplikasi Laravel
docker exec -it sentix-daemon-app-1 bash

# Jalankan migrasi di dalam container
php artisan migrate
exit
```

Dashboard sekarang bisa diakses melalui **http://localhost:8080**.

---

### 3. Kompilasi & Jalankan Sentix Agent (C++)

Agent membutuhkan akses root untuk mengeksekusi script pembersihan cache level kernel.

```bash
cd agent

# Kompilasi native C++ agent
g++ sentix.cpp -o sentix -lpqxx -lpq

# Inject environment variables dan jalankan dengan hak akses penuh (-E)
export $(grep -v '^#' ../.env | xargs)
sudo -E ./sentix
```

---

## 🎯 Fitur Lengkap

### 🛡️ Core Agent (C++ & Bash)

- [x] **Bare-metal Memory Surveillance** — Membaca `/proc/meminfo` secara langsung dari Linux kernel.
- [x] **PostgreSQL Telemetry** — Mengirim data penggunaan RAM secara real-time via libpqxx.
- [x] **Fault-Tolerant Engine** — Menggunakan sistem try-catch loop untuk mencegah crash saat koneksi database terputus.
- [x] **Automated Kernel Healing** — Otomatis memicu eksekusi `heal.sh` untuk membersihkan kernel cache jika penggunaan RAM melebihi 90%.
- [x] **Secure Credentials** — Menggunakan Environment Variables OS untuk mengamankan kredensial database dari hardcoding.

### 📊 Dashboard (Laravel 11 & Livewire 3)

- [x] **Real-time Synchronization** — UI terupdate secara otomatis tanpa browser reload menggunakan fitur Livewire polling.
- [x] **Flux UI Components** — Antarmuka pengguna yang modern, responsif, dan mendukung dark mode.
- [x] **Containerized** — Berjalan sepenuhnya dalam isolasi Docker, menghindari konflik dependensi di lokal.

---

## 🛠️ Tech Stack

**System Level:**
- C++ Native (Core Agent)
- Bash (Action Scripts)
- libpqxx (PostgreSQL C++ API)

**Web Level:**
- Laravel 11 (Backend Framework)
- Livewire 3 (Reactive Frontend)
- Flux UI & TailwindCSS (Styling)

**Infrastructure:**
- Docker & Docker Compose
- PostgreSQL 15 (Alpine Image)
- PHP 8.3 CLI (Alpine Image)

---

## 📂 Project Structure

```plaintext
sentix-daemon/
├── agent/                 # C++ Native Application
│   ├── actions/
│   │   └── heal.sh        # Bash script untuk memory cache clearing
│   └── sentix.cpp         # Main C++ Daemon logic
├── dashboard/             # Laravel 11 Application (Flux UI)
├── docker-compose.yml     # Konfigurasi orkestrasi Docker
└── .env                   # Centralized secrets (ignored by git)
```
