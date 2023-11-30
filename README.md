# Shop Transaction and Database System in C
- [Deskripsi](#deskripsi)
- [Fitur Utama](#fitur-utama)
- [Cara Penggunaan](#cara-penggunaan)
- [Screenshot Aplikasi](#screenshot-aplikasi)

## Deskripsi
Program "Shop Transaction and Database System in C" adalah sebuah program yang dirancang untuk menjalankan sistem pengelolaan transaksi dan basis data di toko. Dengan menggunakan bahasa pemrograman C, program ini bertujuan untuk menjalankan fungsi merekam, mengelola, dan melacak transaksi penjualan serta informasi produk di sebuah toko. Dalam program ini terdapat 2 mode, yaitu mode admin dan mode pelanggan.

## Fitur Utama
1. Manajemen Barang:
   - Fitur untuk menambah, mengedit, dan menghapus barang dari database.
   - Menyimpan informasi barang seperti ID, nama, stok, dan harga.
   - Implementasikan filter untuk mempermudah pencarian barang.

2. Manajemen Membership:
   - Fitur untuk menambah, mengedit, dan menghapus membership dari database.
   - Menyimpan informasi member seperti ID, username, password, nama, no telp, alamat, tanggal regist, dan saldo.
   - Implementasi filter untuk mempermudah pencarian member.
   - Fitur top up saldo dan edit data diri bagi pengguna yang telah mendaftar membership.

3. Transaksi Penjualan:
   - Pelanggan dapat memilih barang untuk dimasukkan ke keranjang untuk dibeli.
   - Hitung total pembelian dan perbarui stok produk setelah transaksi sukses.
   - Menyimpan riwayat transaksi dan struk yang bisa dilihat di mode admin.

4. Tampilan Antarmuka:
   - Input arrow atas dan bawah pada keyboard untuk memilih aksi.
   - Input string yang dibatasi sesuai keperluan (cnth: input khusus huruf, input khusus angka, dsb).
   - Tampilan berwarna.
   - Data barang, member, dan transaksi ditampilkan dalam tabel

## Cara Penggunaan
### Pra-syarat:
- Download source code dan file lainnya (Shop-System-v1.0.0.zip) [di sini](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/releases/tag/v1.0.0).
- Pastikan compiler C (seperti GCC) sudah terinstal di sistem Anda.
- Karena program memanfaatkan ANSI escape sequences untuk mendukung tampilan, aktifkan ANSI escape sequences terlebih dahulu dengan cara mengetikkan
  ```reg add HKCU\Console /v VirtualTerminalLevel /t REG_DWORD /d 1``` di CMD. Sebagai informasi tambahan, ketikkan ```reg delete HKCU\Console /v VirtualTerminalLevel /f``` di CMD untuk menonaktifkan ANSI escape sequences.
  - Tampilan sebelum ANSI escape sequences diaktifkan:  
    ![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/062c372d-839c-4cb0-a77c-cc33dab33f25)
  - Tampilan setelah ANSI escape sequences diaktifkan:  
    ![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/2d8d460a-662f-46be-9b26-ff6196d58526)

### Instalasi:
- Ekstrak file .zip yang sebelumnya didownload.
- Jalankan shortcut ```SHOP APP``` atau masuk ke folder ```source``` lalu jalankan ```main.exe```.
- Jika ada peringantan bahaya dari windows abaikan saja (saya gamasukin virus apa apa, beneran 🙏).
- Jika ```SHOP APP``` dan ```main.exe``` bermasalah, masuk ke folder ```source``` kemudian compile file ```main.c``` untuk mendapatkan file ```main.exe``` yang baru.
- Cara compile:
  - Menggunakan C/C++ IDE
  - Menggunakan CMD
    1. Buka CMD di directori source.
    2. Ketik ```gcc main.c -o main``` di CMD.
    3. Kemudian jalankan file ```main.exe``` atau shotcut ```SHOP APP```.

### Menjalankan Aplikasi:
1. Jalankan shortcut ```SHOP APP``` atau file ```main.exe```.
2. Tekan arrow atas dan bawah serta ```Enter``` pada keyboard untuk menentukan pilihan.
3. Tekan ```Esc``` untuk membatalkan proses atau kembali ke halaman berikutnya.
4. Untuk login ke mode admin, gunakan username ```Admin1``` dan password ```123```.
5. Untuk tampilan yang lebih baik, jalankan program dalam ukuran layar lebar atau full screen.

## Screenshot Aplikasi
### Menu Utama
![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/7bf207a0-5e89-4fb6-88a1-fd6f6964e194)

### Mode Admin
![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/f5887a2d-654b-43f3-bb39-a0be9890b5df)
![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/6683a854-b557-4fe3-8151-70bb39c157ce)
![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/fed4faf0-18ed-4ec0-9659-c97a6311c958)
![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/4ad4dac9-207f-48bb-bf0e-1c04f9b9f781)
![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/e4444601-2957-48e2-a71d-7fc5c70c9176)
![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/e79e587c-f29f-4de2-b24e-45c96a0a167e)
![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/7a817609-24bf-401f-b09e-6b94d1ec2b5e)

### Mode Pelanggan
![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/c00ef09d-79a8-47bb-be1a-b0ca563edd51)
![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/f66bf119-b2c3-4450-99d8-eb80d05801e3)
![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/38eec975-a27a-4e19-b504-7a876568abb6)
![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/cd3827b9-b760-4e60-8b2c-4f6c6b4df4f8)
![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/21106ec0-6d03-41d6-a397-9df90f120a81)
![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/b42ea71e-885a-411f-a771-de5a0c4d0c84)
![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/c4cdd35d-f24d-4ecf-af0e-27b05a4d393a)
![image](https://github.com/mbsaloka/Shop-Transaction-and-Database-System/assets/110384828/75ad21af-eaf2-4190-ba6a-37729997e065)

## Pengembang
Proyek ini dikembangkan oleh:  
[Buyung Saloka](https://instagram.com/mbsaloka)
