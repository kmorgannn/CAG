import sys, serial, argparse, csv, datetime
from time import sleep
    
BAUD = 9600


def print_data(ser):
    line = ser.readline()
    data = [float(val) for val in line.split()]
    # Might be useful if we only want notifications when something is wrong
    # if (data[0] > 5):
    print(data)

# def spamCSV():
#     with open('eggs.csv', 'wb') as csvfile:
#     spamwriter = csv.writer(csvfile, delimiter=' ',
#                             quotechar='|', quoting=csv.QUOTE_MINIMAL)
#     spamwriter.writerow(['Spam'] * 5 + ['Baked Beans'])
#     spamwriter.writerow(['Spam', 'Lovely Spam', 'Wonderful Spam'])

# def writeToCSV(ser):
#     line = ser.readline()
#     data = [float(val) for val in line.split()]
#     csvfile = open('sensor_readings.csv', 'ab')
#         writer = csv.writer(csvfile, delimiter=',')
#         writer.writerow([datetime.datetime.now(), data])
#         csvfile.close()

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
            print_data(ser)
    except KeyboardInterrupt:
        print("Please don't leave!  Think of all the fun times we had together!")
    finally:
        ser.flush()
        ser.close()   

# call main
if __name__ == '__main__':
    main()
