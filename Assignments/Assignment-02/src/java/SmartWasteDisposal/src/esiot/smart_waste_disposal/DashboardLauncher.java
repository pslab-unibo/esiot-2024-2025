package esiot.smart_waste_disposal;

import javax.swing.SwingUtilities;

class DashboardLauncher   {

	static DashboardView view = null;
	static LogView log = null;

	public static void main(String[] args) throws Exception {	
		/*
		if (args.length != 1){
			System.err.println("Args: <serial port>");
			System.exit(1);
		}*/
		SwingUtilities.invokeAndWait(() -> {
			view = new DashboardView();
			log = new LogView();
		});
		String portName = "/dev/cu.usbmodem12101";
		DashboardController contr = new DashboardController(portName,view,log);
		view.registerController(contr);
		SwingUtilities.invokeLater(() -> {
			view.setVisible(true);
			log.setVisible(true);
		});
	}
}