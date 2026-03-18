package DAO; 
import java.util.List; 
import pojo.Cazuri; 
import java.util.Date; 
import pojo.Procese; 
import pojo.Judecatori; 
public interface CazuriDao { 

	public void adaugaCaz (Cazuri cazuri); 
	public List<Cazuri> afiseazaCazuri(); 
	public void modificaCaz (Integer ID_Caz, Judecatori judecator, Procese proces); 
	public void stergeCaz (Integer id); 
}