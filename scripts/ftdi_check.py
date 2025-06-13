# ftdi_check.py

from pyftdi.ftdi import Ftdi
from pyftdi.usbtools import UsbToolsError


def main():
    try:
        print("Scanning for FTDI devices...")
        Ftdi.show_devices()
    except UsbToolsError as e:
        print("USB error:", e)
    except Exception as e:
        print("General error:", e)


if __name__ == "__main__":
    main()
