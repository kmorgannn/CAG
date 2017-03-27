import sys, serial, argparse
from time import sleep
    
BAUD = 9600

# main() function
def main():
    # create parser
    parser = argparse.ArgumentParser(description="LDR serial")
    # add expected arguments
    parser.add_argument('--port', help="the full path of the arduino usb", dest='port', required=True, type=str)
    # parse args
    args = parser.parse_args()

    print('reading from serial port %s...' % args.port)

    ser = serial.Serial(args.port, BAUD)
    try:
        while True:
            line = ser.readline()
            data = [float(val) for val in line.split()]
            print(data)
    except KeyboardInterrupt:
        print("Please don't leave!  Think of all the fun times we had together!")
    finally:
        ser.flush()
        ser.close()    

# call main
if __name__ == '__main__':
    main()
