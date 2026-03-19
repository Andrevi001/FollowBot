import socket
import struct
import numpy as np
import cv2
import math

K = 2556 #costante per misurare la distanza

Width, Height = 160, 120
Fwidth, Fheight = 240, 180

model = cv2.FaceDetectorYN.create("yunet.onnx", "", (Fwidth, Fheight))
model.setInputSize((Fwidth, Fheight))

sock = socket.socket()
sock.bind(('0.0.0.0', 1234))
sock.listen(1)
print("[PC] In attesa di connessione dalla ESP32...")

conn, addr = sock.accept()
print(f"[PC] Connesso da {addr}")

def read_exact(conn, size):
    data = b''
    while len(data) < size:
        try:
            more = conn.recv(size - len(data))
            if not more:
                return None
            data += more
        except socket.timeout:
            print(f"Timeout durante la lettura di {size} byte")
            return None
    return data

try:
    while True:
        
        # 2. Leggi header con timeout
        header = read_exact(conn, 5)

        # 3. Leggi dimensione frame
        size_raw = read_exact(conn, 4)
        if not size_raw:
            break
        frame_size = struct.unpack("<I", size_raw)[0]

        # 4. Ricevi frame
        frame_data = read_exact(conn, frame_size)

        # Conversione da RGB565 a BGR
        rgb565 = np.frombuffer(frame_data, dtype=np.uint16).reshape((Height, Width))
        rgb565 = (rgb565 >> 8) | (rgb565 << 8)

        r = ((rgb565 >> 11) & 0x1F) * 255 // 31
        g = ((rgb565 >> 5) & 0x3F) * 255 // 63
        b = (rgb565 & 0x1F) * 255 // 31

        frame = np.dstack((b, g, r)).astype(np.uint8)
        frame = cv2.flip(frame, -1)
        

        # Face detection
        frame_resized = cv2.resize(frame, (Fwidth, Fheight), interpolation=cv2.INTER_NEAREST)
        _, faces = model.detect(frame_resized)
        
        pan = 0
        tilt = 0
        if faces is not None:
            for face in faces:
                x, y, w, h = face[0:4].astype(int)
                confidence = face[14]
                
                x = int(x * (Width / Fwidth))
                y = int(y * (Height / Fheight))
                w = int(w * (Width / Fwidth))
                h = int(h * (Height / Fheight))

                distance = min(K / math.sqrt(w*h), 255)
                    
                cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0))
                offset_x = (x + w/2) - (Width/2)
                offset_y = (y + h/2) - (Height/2)
                    
                pan = 0
                tilt = 0
                if abs(offset_x) > 5:
                    pan = offset_x * (40/Width) *0.4
                if abs(offset_y) > 5: 
                    tilt = offset_y * (30/Height)*0.4

                conn.send(b"\x80" + int(pan).to_bytes(1, 'little', signed=True) + int(tilt).to_bytes(1, 'little', signed=True) + int(distance).to_bytes(1, 'little'))
        else: 
            conn.send(b"\x90" + b"\x90" + b"\x90" +b"\x90")

        cv2.imshow("ESP32 Stream", frame)
        if cv2.waitKey(1) == 27:
            break

except KeyboardInterrupt:
    print("\nInterruzione da tastiera")

finally:
    conn.close()
    sock.close()
    cv2.destroyAllWindows()
