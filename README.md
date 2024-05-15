# PA Kelompok4-Praktikum-IOT-Unmul
# Kelompok 4 IOT C 2022
1. Aprisa Idma Mutiara (2209106001)
2. Narupa Rangga Goroguta (2209106004)
3. Juniver Veronika Lili (2209106013)

## Sistem pendeteksi suhu tubuh manusia menggunakan sensor gerak dan IR     temperature
**Deskripsi :**
Sistem ini dibuat untuk memonitoring suhu tubuh manusia melalui gerakan. Untuk mengetahui perubahan data dari suhu tubuh, sistem ini menggunakan lampu led dan buzzer sebagai tanda. 
Sistem ini terdiri dari 3 komponen utama (LED, Buzzer, sensor gerak (PIR), sensor IR temperature (gy-906)). Pada sistem ini, sensor gerak akan mendeteksi gerakan dari manusia, jika manusia lewat dihadapan sensor gerak maka sensor IR temperature akan diaktifkan dan terdapat delay. LED digunakan untuk mengetahui perubahan suhu tubuh yang diterima dari sensor IR temperature. Jika suhu tubuh kurang dari 27 derajat celcius maka lampu hijau akan menyala. jika suhu tubuh berada pada rentang 27 - 30 derajat celcius maka lampu kuning nyala dan jika suhu tubuh lebih dari 30 maka lampu merah nyala dan buzzer berbunyi. Informasi yang diterima akan dikirimkan ke platform blynk dan akan dikonversikan menjadi Celcius, Fahrenheit dan Kelvin yang ditampilkan ke dashboard. 

**Pembagian tugas :**
1. Aprisa Idma Mutiara : membuat struktur kodingan 
2. Narupa Rangga Goroguta : membuat rangkaian our schematic
3. Juniver Veronika Lili : membuat rangkaian board schematic

**Komponen yang Digunakan :**
1. Kabel jumper
2. LED
3. Resistor
4. Breadboard
5. ESP8266
6. Kabel MicroUSB
7. Buzzer
8. Sensor gerak (PIR)
9. sensor IR temperature (gy-906)
   
**Our Schematic Publisher**
![pub](https://github.com/aprisamutiara/pa-praktikum-iot-unmul-c4/assets/123526722/ec2a4045-f7ee-48ad-ab2e-078cc76c7eb3)

**Our Schematic Subscriber**
![sub1](https://github.com/aprisamutiara/pa-praktikum-iot-unmul-c4/assets/123526722/53cc4368-8fcb-4749-8799-0fcf18c8b5f2)

**Board Schematic Publisher & Subscriber**
![board skema](https://github.com/aprisamutiara/pa-praktikum-iot-unmul-c4/assets/123526722/388da9f3-b654-40d9-8977-2b31594e1e32)

