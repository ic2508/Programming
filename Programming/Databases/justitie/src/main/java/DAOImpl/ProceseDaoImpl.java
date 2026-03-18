package DAOImpl; 

import java.sql.Date;

import java.util.ArrayList; 
import java.util.List; 
import jakarta.persistence.Query; 
import org.hibernate.Session; 
import org.hibernate.Transaction;

import pojo.Judecatori;
import pojo.Procese; 
import DAO.ProceseDao; 

public class ProceseDaoImpl implements ProceseDao{ 
	public void adaugaProces(Procese proces) { 
		Session session = HibernateUtil.getSessionFactory().openSession(); 
		Transaction transaction = session.beginTransaction(); 
		session.persist(proces); 
		transaction.commit(); 
		session.close(); 
	}
	public List<Procese> afiseazaProcese() { 
		List<Procese> listaProcese = new ArrayList(); 
		Session session = HibernateUtil.getSessionFactory().openSession(); 
	    jakarta.persistence.TypedQuery<Procese> query =
	            session.createQuery("From Procese", Procese.class);
		listaProcese = query.getResultList(); 
		session.close();
		return listaProcese; 
	}
	public void modificaProces(int ID_Proces,
            String Numar_Dosar,
            String Tip_Proces,
            String Stadiu,
            String Data_Inregistrarii,
            String Denumire) {

	Session session = HibernateUtil.getSessionFactory().openSession();
	Transaction transaction = session.beginTransaction();

	Procese detaliiprocese = session.find(Procese.class, ID_Proces);

	if (Numar_Dosar != null && !Numar_Dosar.trim().isEmpty()) {
	detaliiprocese.setNumar_Dosar(Numar_Dosar.trim());
	}
	if (Tip_Proces != null && !Tip_Proces.trim().isEmpty()) {
	detaliiprocese.setTip_Proces(Tip_Proces.trim());
	}
	if (Stadiu != null && !Stadiu.trim().isEmpty()) {
	detaliiprocese.setStadiu(Stadiu.trim());
	}
	if (Data_Inregistrarii != null && !Data_Inregistrarii.trim().isEmpty()) {
		detaliiprocese.setData_Inregistrarii(Date.valueOf(Data_Inregistrarii.trim()));
    }
    if (Denumire != null && !Denumire.trim().isEmpty()) {
    	detaliiprocese.setDenumire(Denumire.trim());
    }

	session.merge(detaliiprocese);
	transaction.commit();
	session.close();
	}

	public void stergeProces(Procese proces) {
        Session session = HibernateUtil.getSessionFactory().openSession();
        Transaction transaction = session.beginTransaction();

        try {
            int idProces = proces.getID_Proces();

            session.createMutationQuery(
                    "delete from Cazuri c where c.procese.ID_Proces = :id")
                   .setParameter("id", idProces)
                   .executeUpdate();

            Procese p = session.find(Procese.class, idProces);
            if (p != null) {
                session.remove(p); 
            }

            transaction.commit();
        } catch (Exception e) {
            if (transaction != null) {
                transaction.rollback();
            }
            throw e;
        } finally {
            session.close();
        }
    }
	
	public void stergeToateProcesele() {

	    Session session = HibernateUtil.getSessionFactory().openSession();
	    Transaction tx = null;

	    try {
	        tx = session.beginTransaction();

	        session.createMutationQuery(
	                "delete from Cazuri"
	        ).executeUpdate();

	        session.createMutationQuery(
	                "delete from Procese"
	        ).executeUpdate();

	        tx.commit();
	    } catch (Exception e) {
	        if (tx != null) tx.rollback();
	        e.printStackTrace();
	    } finally {
	        session.close();
	    }
	}
}