package pojo; 

import java.util.HashSet; 
import java.sql.Date;

import java.util.Set; 

public class Judecatori  implements java.io.Serializable { 
	private Integer ID_Judecator; 
	private String Nume_Judecator; 
	private String Prenume_Judecator; 
	private String CNP; 
	private Date Data_Nasterii;
    private String Grad;
	private Set Cazuri = new HashSet(0); 

	public Judecatori() { 
	} 

	public Judecatori(String Nume_Judecator, String Prenume_Judecator, String CNP, Set Cazuri) { 
		this.Nume_Judecator = Nume_Judecator; 
		this.Prenume_Judecator = Prenume_Judecator; 
		this.CNP = CNP; 
		this.Cazuri = Cazuri; 
	} 

	public Integer getID_Judecator() { 
		return this.ID_Judecator; 
	} 

	public void setID_Judecator(Integer ID_Judecator) { 
		this.ID_Judecator = ID_Judecator; 
	} 
	public String getNume_Judecator() { 
		return this.Nume_Judecator; 
	} 

	public void setNume_Judecator(String Nume_Judecator) { 
		this.Nume_Judecator = Nume_Judecator; 
	} 
	public String getPrenume_Judecator() { 
		return this.Prenume_Judecator; 



	} 

	public void setPrenume_Judecator(String Prenume_Judecator) { 
		this.Prenume_Judecator = Prenume_Judecator; 
	} 
	public String getCNP() { 
		return this.CNP; 
	} 

	public void setCNP(String CNP) { 
		this.CNP = CNP; 
	} 
	public Set getCazuri() { 
		return this.Cazuri; 
	} 

	public void setCazuri(Set Cazuri) { 
		this.Cazuri = Cazuri; 
	} 
	
	 public Date getData_Nasterii() {
	        return Data_Nasterii;
	    }

	    public void setData_Nasterii(Date data_Nasterii) {
	        Data_Nasterii = data_Nasterii;
	    }

	    public String getGrad() {
	        return Grad;
	    }

	    public void setGrad(String grad) {
	        Grad = grad;
	    }
}
 