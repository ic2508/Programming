package pojo; 
import java.sql.Date;

import java.util.HashSet; 

import java.util.Set; 
public class Procese  implements java.io.Serializable { 
	private Integer ID_Proces; 
	private String Numar_Dosar; 
	private String Tip_Proces; 
	private String Stadiu; 
	private Date Data_Inregistrarii;
    private String Denumire;



	private Set Cazuri = new HashSet(0); 

	public Procese() { 
	} 

	public Procese(String Numar_Dosar, String Tip_Proces, String Stadiu, Set Cazuri) { 
		this.Numar_Dosar = Numar_Dosar; 
		this.Tip_Proces = Tip_Proces; 
		this.Stadiu = Stadiu; 
		this.Cazuri = Cazuri; 
	} 

	public Integer getID_Proces() { 
		return this.ID_Proces; 
	} 

	public void setID_Proces(Integer ID_Proces) { 
		this.ID_Proces = ID_Proces; 
	} 
	public String getNumar_Dosar() { 
		return this.Numar_Dosar; 
	} 

	public void setNumar_Dosar(String Numar_Dosar) { 
		this.Numar_Dosar = Numar_Dosar; 
	} 
	public String getTip_Proces() { 
		return this.Tip_Proces; 
	} 

	public void setTip_Proces(String Tip_Proces) { 
		this.Tip_Proces = Tip_Proces; 
	} 
	public String getStadiu() { 
		return this.Stadiu; 
	} 

	public void setStadiu(String Stadiu) { 
		this.Stadiu = Stadiu; 
	} 
	
	public Date getData_Inregistrarii() {
        return Data_Inregistrarii;
    }

    public void setData_Inregistrarii(Date data_Inregistrarii) {
        Data_Inregistrarii = data_Inregistrarii;
    }

    public String getDenumire() {
        return Denumire;
    }

    public void setDenumire(String denumire) {
        Denumire = denumire;
    }
	
	
	public Set getCazuri() { 
		return this.Cazuri; 
	} 




	public void setCazuri(Set Cazuri) { 
		this.Cazuri = Cazuri; 
	} 
} 