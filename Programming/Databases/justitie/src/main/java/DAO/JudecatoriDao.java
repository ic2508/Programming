package DAO; 
import java.sql.Date;
import java.util.List; 
import pojo.Judecatori; 
public interface JudecatoriDao { 
	
	public void adaugaJudecator (Judecatori judecator); 
	public List<Judecatori> afiseazaJudecatori(); 
	public void modificaJudecator (int ID_Judecator, String Nume_Judecator, String Prenume_Judecator, String CNP, String Data_Nasterii, String Grad); 
	public void stergeJudecator (Judecatori judecator); 
}

