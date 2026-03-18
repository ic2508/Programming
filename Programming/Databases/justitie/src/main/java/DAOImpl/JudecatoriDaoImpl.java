package DAOImpl; 
import java.sql.Date;
import java.util.ArrayList; 
import java.util.List; 
import jakarta.persistence.Query; 
import org.hibernate.Session; 
import org.hibernate.Transaction;

import pojo.Cazuri;
import pojo.Judecatori; 
import DAO.JudecatoriDao; 

public class JudecatoriDaoImpl implements JudecatoriDao{ 

	public void adaugaJudecator(Judecatori judecator) { 
		Session session = HibernateUtil.getSessionFactory().openSession(); 
		Transaction transaction = session.beginTransaction(); 
		session.persist(judecator); 
		transaction.commit(); 
		session.close(); 
	} 

	public List<Judecatori> afiseazaJudecatori() { 
		List<Judecatori> listaJudecatori = new ArrayList(); 
		Session session = HibernateUtil.getSessionFactory().openSession(); 
		jakarta.persistence.TypedQuery<Judecatori> query =
	            session.createQuery("From Judecatori", Judecatori.class);
		listaJudecatori = query.getResultList(); 
		session.close(); 
		return listaJudecatori; 
	}
	public void modificaJudecator(int ID_Judecator,
            String Nume_Judecator,
            String Prenume_Judecator,
            String CNP,
            String Data_Nasterii,
            String Grad) {
		Session session = HibernateUtil.getSessionFactory().openSession();
		Transaction transaction = session.beginTransaction();

		Judecatori detaliijudecatori = session.find(Judecatori.class, ID_Judecator);

		if (Nume_Judecator != null && !Nume_Judecator.trim().isEmpty()) {
			detaliijudecatori.setNume_Judecator(Nume_Judecator.trim());
		}
		if (Prenume_Judecator != null && !Prenume_Judecator.trim().isEmpty()) {
			detaliijudecatori.setPrenume_Judecator(Prenume_Judecator.trim());
		}
		if (CNP != null && !CNP.trim().isEmpty()) {
			detaliijudecatori.setCNP(CNP.trim());
		}
		if (Data_Nasterii != null && !Data_Nasterii.trim().isEmpty()) {
			detaliijudecatori.setData_Nasterii(Date.valueOf(Data_Nasterii.trim()));
	    }
	    if (Grad != null && !Grad.trim().isEmpty()) {
	    	detaliijudecatori.setGrad(Grad.trim());
	    }

		session.merge(detaliijudecatori);
		transaction.commit();
		session.close();
	}
	 public void stergeJudecator(Judecatori judecator) {
	        int idJudecator = judecator.getID_Judecator();

	        Session session = HibernateUtil.getSessionFactory().openSession();
	        Transaction tx = null;
	        try {
	            tx = session.beginTransaction();

	            session.createMutationQuery(
	                    "delete from Cazuri c where c.judecatori.ID_Judecator = :id")
	                   .setParameter("id", idJudecator)
	                   .executeUpdate();


	            Judecatori j = session.find(Judecatori.class, idJudecator);
	            if (j != null) {
	                session.remove(j);
	            }

	            tx.commit();
	        } catch (Exception e) {
	            if (tx != null) tx.rollback();
	            throw e;
	        } finally {
	            session.close();
	        }
	    }
	 
	 public void stergeTotiJudecatorii() {
	        Session session = HibernateUtil.getSessionFactory().openSession();
	        Transaction tx = null;

	        try {
	            tx = session.beginTransaction();

	            session.createMutationQuery("delete from Cazuri").executeUpdate();
	            session.createMutationQuery("delete from Judecatori").executeUpdate();

	            tx.commit();
	        } catch (Exception e) {
	            if (tx != null) tx.rollback();
	            throw e;
	        } finally {
	            session.close();
	        }
	    }
	 

}