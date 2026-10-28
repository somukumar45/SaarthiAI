
import serial
import time

PORT = "COM17"  # Change this if your Arduino uses another port

try:
    arduino = serial.Serial(PORT, 9600, timeout=1)
    time.sleep(2)
    print("SaarthiAI connected!")

    print("F = Forward")
    print("B = Backward")
    print("L = Left")
    print("R = Right")
    print("S = Stop")
    print("Q = Quit")

    while True:
        command = input("Enter command: ").strip().upper()

        if command in ["F", "B", "L", "R", "S"]:
            arduino.write(command.encode("ascii"))
            arduino.flush()
            print("Sent:", command)

        elif command == "Q":
            arduino.write(b"S")
            arduino.flush()
            break

        else:
            print("Invalid command")

except serial.SerialException as e:
    print("Serial connection error:", e)

finally:
    if "arduino" in locals() and arduino.is_open:
        arduino.close()
    print("Connection closed.")
