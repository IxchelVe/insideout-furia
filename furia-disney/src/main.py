import serial
import time
import vlc
import pygame

# Configuración de los archivos de video
REPOSO_VIDEO = "/home/ixchelvelazquezcaballero/insideout/videos/reposo.mp4"
STARTGAME_VIDEO = "/home/ixchelvelazquezcaballero/insideout/videos/startgame.mp4"
FUERZA_VIDEOS = {
    "bajo": "/home/ixchelvelazquezcaballero/insideout/videos/fuerza_baja.mp4",
    "medio": "/home/ixchelvelazquezcaballero/insideout/videos/fuerza_media.mp4",
    "alto": "/home/ixchelvelazquezcaballero/insideout/videos/fuerza_alta.mp4",
    "maximo": "/home/ixchelvelazquezcaballero/insideout/videos/fuerza_maxima.mp4"
}

# Configuración del puerto serial
ser = serial.Serial('/dev/ttyUSB0', 57600, timeout=5)

# Inicializar Pygame en pantalla completa
pygame.init()
screen = pygame.display.set_mode((0, 0), pygame.FULLSCREEN)
pygame.display.set_caption("Video Player")

# Función para limpiar la pantalla
def clear_screen():
    screen.fill((0, 0, 0))
    pygame.display.update()

# Función para reproducir un video
def play_video(video_path):
    clear_screen()
    player = vlc.MediaPlayer(video_path)
    player.set_fullscreen(True)
    player.play()
    time.sleep(1)  # Esperar un momento para asegurarse de que el video comience
    return player

# Función para detener la reproducción del video
def stop_video(player):
    if player:
        player.stop()

# Función principal del juego
def main():
    while True:
        # Reproducir el video de reposo
        print("Reproduciendo video de reposo...")
        current_player = play_video(REPOSO_VIDEO)

        # Esperar el primer golpe
        game_started = False
        while not game_started:
            # Leer el valor del sensor de fuerza desde el Arduino
            input_str = ser.readline().decode('utf-8').strip()
            print(f"Primer golpe - Raw input from Arduino: '{input_str}'")

            try:
                accel_scale_modifier, _ = map(float, input_str.split())
                print(f"Accel Scale Modifier (primer golpe): {accel_scale_modifier}")
            except ValueError:
                continue

            if accel_scale_modifier > 50:  # Umbral para detectar el primer golpe
                game_started = True
                stop_video(current_player)
                print("Reproduciendo video de startgame...")
                current_player = play_video(STARTGAME_VIDEO)
                time.sleep(6)  # Esperar a que termine el video de startgame
                stop_video(current_player)

        # Esperar el segundo golpe mientras el video de Startgame está en pantalla
        second_hit_received = False
        while not second_hit_received:
            # Leer el valor del sensor de fuerza desde el Arduino
            input_str = ser.readline().decode('utf-8').strip()
            print(f"Segundo golpe - Raw input from Arduino: '{input_str}'")

            try:
                accel_scale_modifier, _ = map(float, input_str.split())
                print(f"Accel Scale Modifier (segundo golpe): {accel_scale_modifier}")
            except ValueError:
                continue

            if accel_scale_modifier > 50:  # Umbral para detectar el segundo golpe
                second_hit_received = True

                # Definir los rangos de fuerza ajustados
                if 50 <= accel_scale_modifier < 100:
                    video_path = FUERZA_VIDEOS["bajo"]
                elif 100 <= accel_scale_modifier < 200:
                    video_path = FUERZA_VIDEOS["medio"]
                elif 200 <= accel_scale_modifier < 300:
                    video_path = FUERZA_VIDEOS["alto"]
                else:
                    video_path = FUERZA_VIDEOS["maximo"]

                print(f"Reproduciendo video para el rango de fuerza: {video_path}")

                # Reproducir el video correspondiente al rango
                current_player = play_video(video_path)
                time.sleep(2)  # Dar tiempo para iniciar la reproducción
                if current_player.is_playing():
                    print("Reproducción iniciada correctamente")
                    while current_player.is_playing():
                        time.sleep(0.1)
                else:
                    print("Error al reproducir el video del rango de fuerza")

                # Detener la reproducción del video actual y volver a iniciar el ciclo principal
                stop_video(current_player)
                print("Video de rango terminado, reiniciando ciclo...")
                break  # Volver al inicio del bucle principal para reiniciar el programa

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("Programa terminado")
        ser.close()
        pygame.quit()
