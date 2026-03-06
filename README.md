# FollowBot: Robot che esegue comandi semplici rilevati tramite gesti

**FollowBot** è un robot mobile a quattro ruote in grado di seguire un volto.  
Il volto viene rilevato tramite OV3660 montata su una **ESP32-WROVER-KIT**, che invia le immagini a un server **Python** per l'elaborazione.  
Il server elabora i dati visivi e restituisce i comandi, che vengono inoltrati al sistema di movimento tramite un collegamento fisico.  
Il movimento è gestito da una seconda **ESP32**.

Se ci sono più volti presenti nel frame il comportamento è imprevedibile.

---

## Caratteristiche
- Rilevamento del volti tramite **ESP32-WROVER-KITS**
- Movimento autonomo 4WD/pan-tilti controllato da **ESP32**
- Elaborazione immagine tramite **Python**

---

## Tecnologie e componenti
- **ESP32** per il controllo del movimento
- **ESP32-WROVER-KIT** per la visione artificiale
- 2x **TB6612FNG** per il controllo dei motori DC
- 2x **Servo motori 180°** per la stabilizzazione dell’immagine e il puntamento
- 4x **Motori DC** per la trazione
- 2x **LM2596** per la regolazione della tensione
- **Wi-Fi** per la comunicazione tra ESP-Visione e server
- **UART** per la cominicazione tra le ESP32.
- 4x **Batterie 18650** per l'alimentazione
- **PlatformIO** per la programmazione
- **Python** sul server per l’elaborazione delle immagini e il riconoscimento dei gesti

---

## Uso
1. Accendere il robot.
2. Una volta stabilita la connessione Wi-Fi col server, il robot inizierà a rilevare il volto e a muoversi in modo autonomo tenendosi tra 100 cm e i 170 cm da volto.
---

## REPO
- /followbot_body contiene il codice relativo al movimento
- /followbot_eyes contiene il codice relativo alla visione
- /server contiene il codice relativo alla elaborazione delle immagini

---

## Licenza
Distribuito sotto licenza **MIT**. Vedi il file `LICENSE` per i dettagli.
