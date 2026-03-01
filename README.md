# 🎛️ STM32 Gömülü Sistem Uygulaması

Bu proje, **ARM Cortex-M4** mimarisine sahip bir STM32 mikrodenetleyicisi üzerinde, C programlama dili kullanılarak donanım seviyesinde geliştirilmiş bir akademik gömülü sistem uygulamasıdır.

## 🎯 Projenin Amacı
Projenin temel amacı, mikrodenetleyicinin iç donanım birimlerini (Timer ve GPIO) en düşük seviyede ve en optimize şekilde kullanarak sistem kaynaklarını verimli yönetmektir. Sürekli döngüler (delay/loop) yerine **Kesme (Interrupt)** mimarisi kullanılarak işlemci (CPU) yükü hafifletilmiştir.

## ⚙️ Teknik Detaylar ve Optimizasyonlar
* **Donanım:** STM32F4 Serisi (168 MHz Core Clock)
* **Kütüphane:** HAL (Hardware Abstraction Layer) 
* **GPIO Yönetimi:** İlgili portun saat hattı (Clock) aktif edilerek, Push-Pull modunda çıkış (Output) pini yapılandırıldı.
* **Timer (Zamanlayıcı) Optimizasyonu:**
  * 168 MHz'lik yüksek frekanslı sistem saatine uygun olarak Prescaler (Bölücü) ve Auto-Reload Register (ARR) değerleri matematiksel olarak hesaplandı.
  * Bloklayıcı gecikme fonksiyonları (`HAL_Delay`) kullanmak yerine, Timer Donanım Kesmeleri (Timer Interrupts) kullanıldı. Bu sayede işlemci diğer görevleri yerine getirebilirken, zamanlama donanımsal olarak arka planda sıfır hata ile çalışır.

## 📂 Klasör Yapısı
* `Core/Src/main.c`: Konfigürasyonların ve donanım kesme fonksiyonlarının bulunduğu ana mantık dosyası.
* `Core/Inc/main.h`: Gerekli kütüphane bağlantılarının tanımlandığı başlık dosyası.
