package esiot.smart_waste_disposal;

public class DashboardController  {

	static final String MSG_MAINTENANCE_DONE 	= "ok";
	static final String MSG_DISCHARGE 			= "di";
	
	SerialCommChannel channel;
	DashboardView view;
	LogView logger;
	
	public DashboardController(String port, DashboardView view, LogView logger) throws Exception {
		this.view = view;
		this.logger = logger;
		
		channel = new SerialCommChannel(port,115200);		
		new MonitoringAgent(channel,view,logger).start();
			
		/* attesa necessaria per fare in modo che Arduino completi il reboot */
		
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");		
	
	}
	
	public void notifyMaintenanceDone() {
		  channel.sendMsg(MSG_MAINTENANCE_DONE);
	}

	public void notifyDischarge() {
		  channel.sendMsg(MSG_DISCHARGE);
	}

}
