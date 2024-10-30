package esiot.module_lab_2_2;

/**
 *
 */
public class SimpleSerialMonitor  {

	private static String DEFAULT_SERIAL_PORT_NAME = "/dev/tty.usbmodem1422401"; /* to be changed depending on the system */
	
	public static void main(String[] args) throws Exception {

		String comPortName = DEFAULT_SERIAL_PORT_NAME; // args[0];

		if (args.length > 0){
			comPortName = args[0];
		} 
		
		System.out.println("Start monitoring serial port "+comPortName+" at 9600 boud rate");
		
		try {
			SerialMonitor monitor = new SerialMonitor();
			monitor.start(comPortName);							
			Thread.sleep(1000000);
		} catch (InterruptedException ex) {
			ex.printStackTrace();
		}
	}
}