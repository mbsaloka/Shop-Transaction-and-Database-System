# Shop Transaction and Database System in C
- Deskripsi
- Fitur Utama
- Cara Penggunaan

## Deskripsi
Program "Shop Transaction and Database System in C" adalah sebuah sistem yang dirancang untuk memudahkan pengelolaan transaksi dan basis data di toko. Dengan menggunakan bahasa pemrograman C, program ini bertujuan untuk menjalankan fungsi merekam, mengelola, dan melacak transaksi penjualan serta informasi produk di sebuah toko. Dalam program ini terdapat 2 mode, yaitu mode admin dan mode pelanggan.

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
- Pastikan compiler C (seperti GCC) sudah terinstal di sistem Anda.
- Karena program memanfaatkan ANSI escape sequences untuk mendukung tampilan, aktifkan ANSI escape sequences terlebih dahulu dengan cara mengetikkan
  ```reg add HKCU\Console /v VirtualTerminalLevel /t REG_DWORD /d 1``` di CMD.
  Sebagai informasi tambahan, ketikkan
  ```reg delete HKCU\Console /v VirtualTerminalLevel /f``` di CMD untuk menonaktifkan ANSI escape sequences

Instalasi:

(Tambahkan instruksi instalasi jika diperlukan)
Menjalankan Aplikasi:

(Berikan langkah-langkah untuk menjalankan aplikasi)
Kontribusi
Kami sangat menghargai kontribusi dari para pengembang. Jika Anda ingin berkontribusi pada proyek ini, silakan lakukan langkah-langkah berikut:

(Tambahkan langkah-langkah untuk kontribusi)
Laporan Masalah (Bug) dan Fitur Baru
Jika Anda menemui bug atau memiliki ide untuk fitur baru, silakan buka issue di repositori ini.

Lisensi
Proyek ini dilisensikan di bawah [nama_lisensi]. Untuk detail lebih lanjut, silakan lihat berkas LISENSI.

Pengembang
Proyek ini dikembangkan oleh:

[Nama Pengembang 1]
[Nama Pengembang 2]
Terima kasih atas kontribusi dari seluruh tim pengembang!
