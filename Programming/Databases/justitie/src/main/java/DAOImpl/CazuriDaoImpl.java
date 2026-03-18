package DAOImpl; 
import java.util.ArrayList; 
import java.util.List; 
import jakarta.persistence.Query; 
import org.hibernate.Session; 
import org.hibernate.Transaction; 
import pojo.Cazuri; 
import DAO.CazuriDao; 
import java.util.Date; 
import pojo.Procese; 
import pojo.Judecatori; 

public class CazuriDaoImpl implements CazuriDao{ 
	public void adaugaCaz(Cazuri cazuri) {
	    Session session = HibernateUtil.getSessionFactory().openSession();
	    Transaction transaction = null;
	    try {
	        transaction = session.beginTransaction();
	        session.persist(cazuri);
	        transaction.commit();
	    } catch (Exception e) {
	        if (transaction != null) {
	            transaction.rollback();
	        }
	        e.printStackTrace();
	        throw e;
	    } finally {
	        session.close();
	    }
	}

	public List<Cazuri> afiseazaCazuri() { 
		List<Cazuri> listaCaz = new ArrayList(); 
		Session session = HibernateUtil.getSessionFactory().openSession(); 
		jakarta.persistence.TypedQuery<Cazuri> query =
	            session.createQuery("FROM Cazuri c ORDER BY c.ID_Caz", Cazuri.class);
		listaCaz = query.getResultList(); 
		session.close();
		
		return listaCaz; 
	} 

	public void modificaCaz(Integer ID_Caz, Judecatori judecator, Procese proces) { 
		Session session = HibernateUtil.getSessionFactory().openSession(); 
		Transaction transaction = session.beginTransaction(); 
		Cazuri detaliicazuri; 
		detaliicazuri = session.find(Cazuri.class, ID_Caz);
		detaliicazuri.setJudecatori(judecator); 
		detaliicazuri.setProcese(proces); 
		session.merge(detaliicazuri); 
		transaction.commit(); 
		session.close(); 
	} 

	public void stergeCaz(Integer id) {
	    Session session = HibernateUtil.getSessionFactory().openSession();
	    session.beginTransaction();

	    Cazuri caz = session.find(Cazuri.class, id);
	    if (caz != null) {
	        session.remove(caz);
	    }

	    session.getTransaction().commit();
	    session.close();
	}
	
	public boolean existaCombinatie(Integer idJudecator, Integer idProces) {

	    try (Session session = HibernateUtil.getSessionFactory().openSession()) {

	        jakarta.persistence.TypedQuery<Long> query = session.createQuery(
	            "SELECT COUNT(c) FROM Cazuri c " +
	            "WHERE c.judecatori.ID_Judecator = :jud " +
	            "AND c.procese.ID_Proces = :proc",
	            Long.class
	        );

	        query.setParameter("jud", idJudecator);
	        query.setParameter("proc", idProces);

	        Long count = query.getSingleResult();
	        return count != null && count > 0;
	    }
	}
	
	public void stergeToateCazurile() {

	    Session session = HibernateUtil.getSessionFactory().openSession();
	    Transaction tx = null;

	    try {
	        tx = session.beginTransaction();

	        session.createMutationQuery("DELETE FROM Cazuri")
	               .executeUpdate();

	        tx.commit();
	    } catch (Exception e) {
	        if (tx != null) tx.rollback();
	        e.printStackTrace();
	    } finally {
	        session.close();
	    }
	}
} 