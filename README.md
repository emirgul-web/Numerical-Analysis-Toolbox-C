# 🧮 Numerical Analysis Toolbox (C Based)

![Language](https://img.shields.io/badge/Language-C-blue)
![Topic](https://img.shields.io/badge/Topic-Numerical%20Analysis-green)
![Feature](https://img.shields.io/badge/Feature-Expression%20Parser-orange)

Bu proje, mühendislik problemlerinin çözümünde kullanılan 10 farklı **Sayısal Analiz yöntemini** tek bir çatı altında toplayan, C dili ile geliştirilmiş kapsamlı bir hesaplama aracıdır.

Projenin en güçlü yönü, matematiksel fonksiyonların kod içine gömülü (hardcoded) olmak zorunda olmamasıdır. Geliştirilen **Özel İfade Ayrıştırıcı (Custom Expression Parser)** sayesinde, kullanıcı `x^3 - 2*sin(x)` gibi ifadeleri konsola yazdığında, program bu ifadeyi algılar ve işler.

## 🚀 Öne Çıkan Özellikler

### 1. Dinamik Matematiksel Ayrıştırıcı (Math Parser)
Kullanıcıdan `string` olarak alınan matematiksel ifadeleri (Polinomlar, Trigonometrik, Logaritmik, Üstel) analiz eder.
* **Desteklenen Yapılar:** `sin`, `cos`, `tan`, `log`, `ln`, `exp`, `^` (kuvvet), `*`, `/`, `+`, `-`.
* **Algoritma:** İşlem önceliğini ve parantezleri dikkate alan **Recursive Descent Parser** mantığı kullanılmıştır.

### 2. Kök Bulma Algoritmaları
Lineer olmayan denklemlerin köklerini bulmak için 3 farklı yöntem sunar:
* **Bisection (İkiye Bölme):** Aralığı sürekli ikiye bölerek köke yaklaşır.
* **Regula-Falsi:** Doğrusal interpolasyon ile daha hızlı yakınsama sağlar.
* **Newton-Raphson:** Türev kullanarak köke en hızlı yaklaşan yöntemdir (Sayısal türev motoru ile entegre çalışır).

### 3. Lineer Cebir Çözümleri
* **Matris Tersi (Inverse):** Gauss-Jordan eliminasyonu ile $N \times N$ matrislerin tersini alır.
* **Gauss-Seidel:** Lineer denklem sistemlerini iteratif olarak çözer.
* **Cholesky Ayrıştırması:** Simetrik pozitif tanımlı matrisleri $L \cdot L^T$ şeklinde ayrıştırır.

### 4. İntegral ve Türev (Calculus)
* **Sayısal Türev:** İleri, Geri ve Merkezi fark yöntemleri ile türev hesaplar.
* **Sayısal İntegral:** Simpson (1/3 ve 3/8 kuralları) ve Trapez yöntemleri ile belirli integralleri hesaplar.
* **Enterpolasyon:** Gregory-Newton yöntemi ile bilinmeyen ara değerleri tahmin eder.

## 📂 Proje Yapısı

```bash
Numerical-Analysis-Toolbox-C/
├── src/
│   └── main.c          # Tüm algoritmaları ve Parser yapısını içeren ana kod
├── docs/
│   └── Proje_Raporu.pdf # Algoritma detayları ve kullanım kılavuzu
└── README.md
