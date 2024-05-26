import javax.swing.*;
 import java.awt.*; 
import java.awt.event.*; 
class Mybuttons extends JFrame implements ActionListener {     
//variables     
JButton b1,b2,b3;     
Container c; 
 
    //parameterised constructor
     Mybuttons(String st)     {        
 //create Container         
c = getContentPane(); 
 
        //set a layout for a container 
        c.setLayout(new FlowLayout()); 
                 //3 push buttons         
b1 = new JButton();         
b1.setLabel("Red");         
b2 = new JButton("Green");        
 b3 = new JButton("Blue");                  
//specify location of Buttons in the frame         
b1.setBounds(50,50,75,40);         
b2.setBounds(50,120,75,40);         
b3.setBounds(50,190,75,40);                  
//add to frame         
c.add(b1);         
c.add(b2);         
c.add(b3);                  
//add actionlistener to buttons        
 b1.addActionListener(this);        
 b2.addActionListener(this);        
 b3.addActionListener(this);                 
 //close the frame        
 this.addWindowListener(new WindowAdapter()         {           
  public void windowClosing(WindowEvent e)             {               
  System.exit(0);         
    }     
    });     
}//end of constructor      
    public void actionPerformed(ActionEvent ae)     {        
 //to know label of button clicked by the user       
  String str = ae.getActionCommand();         
         if(str.equals("Red"))       
      c.setBackground(Color.red);      
   else if(str.equals("Blue"))           
  c.setBackground(Color.blue);      
   else        
     c.setBackground(Color.green);
     }          
public static void main(String args[])     {   
      Mybuttons mb = new Mybuttons("My Push Buttons");     
    mb.setSize(500,400);                 
mb.setVisible(true); 
}    