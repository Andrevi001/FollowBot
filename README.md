# FollowBot: Robot che esegue comandi semplici rilevati tramite gesti

**FollowBot** è un robot mobile a quattro ruote in grado di eseguire comandi basati su riconoscimento gestuale.  
I gesti vengono rilevati tramite visione artificiale implementata su una **ESP32-S3 CAM**, che invia le immagini a un server per l'elaborazione.  
Il server elabora i dati visivi e restituisce i comandi, che vengono inoltrati al sistema di movimento tramite un collegamento fisico.  
Il movimento è gestito da una seconda **ESP32**.

---

## Caratteristiche
- Rilevamento dei gesti tramite **ESP32-S3 CAM**
- Movimento autonomo 4WD controllato da **ESP32**
- Alimentazione tramite 4 batterie **18650** ricaricabili

---

## Tecnologie e componenti
- **ESP32** per il controllo del movimento
- **ESP32-S3 CAM** per la visione artificiale
- 2x **TB6612FNG** per il controllo dei motori DC
- **HC-SR04** per il rilevamento della distanza
- 2x **Servo motori 180°** per la stabilizzazione dell’immagine e il puntamento
- 4x **Motori DC** per la trazione
- 2x **LM2596** per la regolazione della tensione
- **Wi-Fi** per la comunicazione tra ESP32-CAM e server
- **PlatformIO** o **Arduino IDE** per la programmazione
- **Python** sul server per l’elaborazione delle immagini e il riconoscimento dei gesti

---

## Uso
1. Accendere il robot.
2. Una volta stabilita la connessione Wi-Fi col server, il robot inizierà a rilevare i gesti e a muoversi in modo autonomo secondo i comandi ricevuti.

---

## REPO
- /movimento contiene il codice relativo al movimento
- /visione contiene il codice relativo alla visione
- /elaborazione_img contiene il codice relativo alla elaborazione delle immagini

---

## Licenza
Distribuito sotto licenza **MIT**. Vedi il file `LICENSE` per i dettagli.
