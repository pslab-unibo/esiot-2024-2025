package esiot.smart_waste_disposal;

import java.util.Date;

import javax.swing.*;

class HistoryView extends JFrame  {

	private JTextArea log;

	public HistoryView(){
		super("Log ");
		setSize(600,600);

		JPanel mainPanel = new JPanel();
		log = new JTextArea(30,40);
		log.setEditable(false);
		JScrollPane scrol = new JScrollPane(log);
		mainPanel.add(scrol);
		this.getContentPane().add(mainPanel);
	}

	public void log(String msg){
		SwingUtilities.invokeLater(() -> {
			String date = new Date().toString();
			log.append("["+date+"] "+ msg +"\n");
		});
	}
}
