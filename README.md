# 🧠💥 Inside Out: Activación de la emoción Furia

Este proyecto fue desarrollado para una instalación interactiva inspirada en la película *Inside Out*, donde los participantes activan a la emoción **Furia** golpeando un botón físico. Según la intensidad del golpe, se reproduce un video distinto que representa su nivel de
furia.

> 🎨 También se diseñó un prototipo en Figma para visualizar la interfaz y flujo de usuario de esta experiencia.

---

## ✨ Prototipo UX/UI en Figma

🔗 [Ver prototipo en Figma](https://www.figma.com/proto/TU-LINK-AQUI)

![Prototipo en Figma](https://i.imgur.com/ejemplo.png)  
*Vista previa del prototipo interactivo en Figma*

> Si el enlace o la imagen no carga, asegúrate de tener el archivo de Figma publicado para compartir y reemplaza el link o imagen por los correctos.

---

## ⚙️ Hardware Utilizado

- Arduino UNO
- Sensor de fuerza (acelerómetro)
- Raspberry Pi con Raspbian
- Botón físico golpeable
- Pantalla conectada a la Raspberry Pi

---

## 🎮 Lógica de interacción

1. Se muestra un video de reposo en bucle.
2. Al primer golpe (fuerte), se reproduce el video de inicio (`startgame.mp4`).
3. Se espera un segundo golpe, y dependiendo de la fuerza:
   - Se reproduce un video personalizado (`fuerza_baja`, `media`, `alta`, `máxima`).
4. El sistema vuelve al estado inicial.

---

## 📁 Estructura de Archivos
├── main.py # Script principal que lee desde Arduino y reproduce videos
├── .gitignore # Ignora videos, imágenes pesadas y archivos temporales
├── README.md # Documentación del proyecto
├── videos/ # Carpeta para los archivos de video (.mp4) [no incluidos en el repo]
│ └── .gitkeep
├── images/ # Carpeta para capturas del prototipo o elementos visuales
│ └── .gitkeep
├── hardware/ # Fotos del montaje físico o referencias de conexión
│ └── .gitkeep

---

## 🛠️ Tecnologías usadas

- Python 3
- [PySerial](https://pypi.org/project/pyserial/) para leer datos del Arduino
- [python-vlc](https://pypi.org/project/python-vlc/) para reproducir videos
- [Pygame](https://www.pygame.org/) para pantalla completa y limpieza visual
- Figma para el diseño del prototipo UX/UI

---

## 🚀 Cómo ejecutar

1. Instala dependencias en la Raspberry Pi:

*bash*
sudo apt update
sudo apt install python3-pygame vlc
pip3 install pyserial python-vlc


## ✨ Autora

**Ixchel Velázquez Caballero**  
Desarrolladora de sistemas interactivos, experiencias físicas-digitales, UX/UI y visuales.  
📍 Ciudad de México | 💻 Trabajo remoto  
🔗 [GitHub](https://github.com/IxchelVe)  
✉️ ixvecab@gmail.com

