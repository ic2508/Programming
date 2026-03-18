package pojo; 

import java.util.Date;

public class Cazuri  implements java.io.Serializable { 
	private Integer ID_Caz; 
	private Procese procese; 
	private Judecatori judecatori; 

	public Cazuri() { 
	} 

	public Cazuri(Procese procese, Judecatori judecatori) { 
		this.procese = procese; 
		this.judecatori = judecatori; 



	} 

	public Integer getID_Caz() { 
		return this.ID_Caz; 
	} 

	public void setID_Caz(Integer ID_Caz) { 
		this.ID_Caz = ID_Caz; 
	} 
	public Procese getProcese() { 
		return this.procese; 
	} 

	public void setProcese(Procese procese) { 
		this.procese = procese; 
	} 
	public Judecatori getJudecatori() { 
		return this.judecatori; 
	} 

	public void setJudecatori(Judecatori judecatori) { 
		this.judecatori = judecatori; 
	} 
}