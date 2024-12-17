package esiot.smart_waste_disposal;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.LayoutManager;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.LinkedList;

import javax.swing.*;

class DashboardView extends JFrame implements ActionListener  {

	private JButton maintenanceDone;
	private JButton dischargeContainer;
	
	private JTextField wasteLevelPercentage;
	private JTextField currentTemperature;
	
	private JTextField containerState;
	private DashboardController controller;	
	
	public DashboardView(){
		super(".:: Smart Waste Disposal System ::.");
		setSize(600,150);

		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
		mainPanel.add(Box.createRigidArea(new Dimension(0,20)));

		JPanel infoLine = new JPanel();
		infoLine.setLayout(new BoxLayout(infoLine, BoxLayout.LINE_AXIS));
		containerState = new JTextField("--");
		containerState.setEditable(false);
		containerState.setPreferredSize(new Dimension(200,15));
		infoLine.add(new JLabel("Container State:"));
		infoLine.add(containerState);
		wasteLevelPercentage = new JTextField("--");
		wasteLevelPercentage.setEditable(false);
		wasteLevelPercentage.setPreferredSize(new Dimension(100,15));
		infoLine.add(new JLabel("Waste Level %:"));
		infoLine.add(wasteLevelPercentage);
		currentTemperature = new JTextField("--");
		currentTemperature.setEditable(false);
		currentTemperature.setPreferredSize(new Dimension(200,15));
		infoLine.add(new JLabel("Current Temperature:"));
		infoLine.add(currentTemperature);
		
		mainPanel.add(infoLine);
		mainPanel.add(Box.createRigidArea(new Dimension(0,20)));
		mainPanel.setPreferredSize(new Dimension(200,20));

		JPanel buttonPanel = new JPanel();
		maintenanceDone = new JButton("Maintenance Done");
		maintenanceDone.setEnabled(false);
		maintenanceDone.addActionListener(this);
		dischargeContainer = new JButton("Discharge");
		dischargeContainer.setEnabled(false);
		dischargeContainer.addActionListener(this);
		buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));	    
		buttonPanel.add(dischargeContainer);
		buttonPanel.add(maintenanceDone);
		
		mainPanel.add(buttonPanel);
		mainPanel.add(Box.createRigidArea(new Dimension(0,20)));
		setContentPane(mainPanel);	
		
		addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent ev){
				System.exit(-1);
			}
		});
	}

	public void registerController(DashboardController contr){
		this.controller = contr;
	}

	public void setContainerState(String msg){
		SwingUtilities.invokeLater(() -> {
			containerState.setText(msg); 
		});
	}

	public void setWasteLevel(int perc){
		SwingUtilities.invokeLater(() -> {
			wasteLevelPercentage.setText("" + perc);
		});
	}

	public void setCurrentTemperature(double temp){
		SwingUtilities.invokeLater(() -> {
			currentTemperature.setText("" + temp);
		});
	}

	public void enableAvailable() {
		SwingUtilities.invokeLater(() -> {
			maintenanceDone.setEnabled(false);
			dischargeContainer.setEnabled(false);
		});
	}
	
	public void enableMaintenance() {
		SwingUtilities.invokeLater(() -> {
			maintenanceDone.setEnabled(true);
			dischargeContainer.setEnabled(false);
		});
	}

	public void enableDischarge() {
		SwingUtilities.invokeLater(() -> {
			maintenanceDone.setEnabled(false);
			dischargeContainer.setEnabled(true);
		});
	}

	/*
	public void updateSamples(Sample[] samples) {
		try {
			SwingUtilities.invokeAndWait(() -> {
				graphicPanel.updateSamples(samples);
			});
		} catch (Exception ex) {}
	}

	public void startMaintenanceForRefilling() {
		SwingUtilities.invokeLater(() -> {
			refill.setEnabled(true);
		});
	}

	public void startMaintenanceForRecovering() {
		SwingUtilities.invokeLater(() -> {
			recover.setEnabled(true);
		});
	}
	*/
	
	public void actionPerformed(ActionEvent ev){
		  try {
			  if (ev.getSource() == maintenanceDone){
				  controller.notifyMaintenanceDone();
				  maintenanceDone.setEnabled(false);
			  } else if (ev.getSource() == dischargeContainer){
				  controller.notifyDischarge();
				  dischargeContainer.setEnabled(false);
			  } 
		  } catch (Exception ex){
			  ex.printStackTrace();

		  }
	}
}
