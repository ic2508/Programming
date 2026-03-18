package DAO; 
import java.sql.Date;
import java.util.List; 
import pojo.Procese; 
public interface ProceseDao { 
	
	public void adaugaProces (Procese proces); 
	public List<Procese> afiseazaProcese(); 
	public void modificaProces (int ID_Proces, String Numar_Dosar, String Tip_Proces, String Stadiu, String Data_Inregistrarii, String Denumire); 
	public void stergeProces (Procese proces); 
}