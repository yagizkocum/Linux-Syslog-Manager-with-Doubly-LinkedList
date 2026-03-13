# Linux Syslog Processor using Doubly Linked List

Bu proje, Linux tabanlı sistem günlüklerini (syslog) analiz etmek ve yönetmek için 
**Çift Yönlü Bağlı Liste (Doubly Linked List)** veri yapısını kullanan bir C uygulamasıdır.

##  Özellikler
- **Dinamik Bellek Yönetimi:** Log boyutuna göre RAM kullanımı.
- **Çift Yönlü Gezinme:** Günlükleri hem baştan sona hem de sondan başa (kronolojik/ters kronolojik) listeleyebilme.
- **Hızlı Erişim:** Kuyruk (Tail) işaretçisi ile son kayda anında erişim.

##  Kurulum ve Çalıştırma
Projeyi klonlayın ve derleyin:

```bash
git clone [https://github.com/kullaniciadi/linux-syslog-processor.git](https://github.com/kullaniciadi/linux-syslog-processor.git)
cd linux-syslog-processor
make
./syslog_processor
