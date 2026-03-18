package Controller; 

import DAO.JudecatoriDao; 
import java.io.IOException; 
import java.util.ArrayList; 
import java.util.List; 
import jakarta.servlet.RequestDispatcher; 
import jakarta.servlet.ServletException; 
import jakarta.servlet.http.HttpServlet; 
import jakarta.servlet.http.HttpServletRequest; 
import jakarta.servlet.http.HttpServletResponse; 
import pojo.Judecatori;
import pojo.Procese;
import DAOImpl.JudecatoriDaoImpl; import DAO.JudecatoriDao; 
import java.io.IOException; 
import java.util.ArrayList; 
import java.util.List; 
import jakarta.servlet.RequestDispatcher; 
import jakarta.servlet.ServletException; 
import jakarta.servlet.http.HttpServlet; 
import jakarta.servlet.http.HttpServletRequest; 
import jakarta.servlet.http.HttpServletResponse; 
import pojo.Judecatori; 
import DAOImpl.JudecatoriDaoImpl; 


public class JudecatoriController extends HttpServlet { 

	Judecatori judecator = new Judecatori(); 
	JudecatoriDaoImpl judecatorDaoImpl = new JudecatoriDaoImpl(); 

	protected void doGet(HttpServletRequest request, HttpServletResponse response) 
			throws ServletException, IOException { 
		if (request.getParameter("adaugaJudecator") != null) { 
			String Nume_Judecator = request.getParameter("Nume_Judecator"); 
			String Prenume_Judecator = request.getParameter("Prenume_Judecator"); 
			String CNP = request.getParameter("CNP"); 
			String Data_Nasterii = request.getParameter("Data_Nasterii"); 
			String Grad = request.getParameter("Grad");
			
		    if (Nume_Judecator == null    || Nume_Judecator.isBlank() ||
		            Prenume_Judecator == null || Prenume_Judecator.isBlank() ||
		            CNP == null               || CNP.isBlank() ||
		            Data_Nasterii == null     || Data_Nasterii.isBlank() ||
		            Grad == null              || Grad.isBlank()) {

		            request.setAttribute("eroare", "❌ Toate câmpurile sunt obligatorii pentru adăugarea unui judecător!");
		            RequestDispatcher rd = request.getRequestDispatcher("adauga_judecator.jsp");
		            rd.forward(request, response);
		            return;
		        }
		    
		    if (!CNP.matches("\\d{13}")) {
		        request.setAttribute("eroare", "❌ CNP invalid! Trebuie să conțină exact 13 cifre.");
		        request.getRequestDispatcher("adauga_judecator.jsp").forward(request, response);
		        return;
		    }

		       
		        java.sql.Date data;
		        try {
		        	data = java.sql.Date.valueOf(Data_Nasterii);
		        } catch (IllegalArgumentException e) {
		            request.setAttribute("eroare", "❌ Data nașterii trebuie să fie în formatul yyyy-MM-dd!");
		            RequestDispatcher rd = request.getRequestDispatcher("adauga_judecator.jsp");
		            rd.forward(request, response);
		            return;
		        }
		        
			java.sql.Date dataSQL = java.sql.Date.valueOf(Data_Nasterii);
			judecator = new Judecatori();
			judecator.setNume_Judecator(Nume_Judecator); 
			judecator.setPrenume_Judecator(Prenume_Judecator); 
			judecator.setCNP(CNP); 
			judecator.setData_Nasterii(dataSQL);
			judecator.setGrad(Grad);
			judecatorDaoImpl.adaugaJudecator(judecator); 
			
			request.setAttribute("succes", "✔️ Judecătorul a fost adăugat cu succes!");

		    request.getRequestDispatcher("adauga_judecator.jsp").forward(request, response);
		    return;
		} 
	} 


	protected void doPost(HttpServletRequest request, HttpServletResponse response) 
	        throws ServletException, IOException { 

	    request.setCharacterEncoding("UTF-8");

	    if (request.getParameter("afiseazaJudecatori") != null) { 
	        List<Judecatori> listaJudecatori = new ArrayList<>(); 
	        listaJudecatori = judecatorDaoImpl.afiseazaJudecatori(); 
	        request.setAttribute("listaJudecatori", listaJudecatori); 
	        RequestDispatcher rd = request.getRequestDispatcher("tabela_judecatori.jsp"); 
	        rd.forward(request, response); 
	        return;
	    } 

	    if (request.getParameter("modificaJudecator") != null) { 

	        String idStr = request.getParameter("ID_Judecator");

	        if (idStr == null || idStr.isBlank()) {
	            request.setAttribute("eroare", "❌ Trebuie selectat un judecător pentru modificare.");
	            request.getRequestDispatcher("tabela_judecatori.jsp")
	                   .forward(request, response);
	            return;
	        }

	        int id1 = Integer.parseInt(idStr); 

	        String Nume_Judecator = request.getParameter("Nume_Judecator"); 
	        String Prenume_Judecator = request.getParameter("Prenume_Judecator"); 
	        String CNP = request.getParameter("CNP"); 
	        String Data_Nasterii = request.getParameter("Data_Nasterii"); 
	        String Grad = request.getParameter("Grad"); 

	        if (CNP == null || !CNP.matches("\\d{13}")) {
	            request.setAttribute(
	                "eroare",
	                "❌ CNP-ul trebuie să conțină exact 13 cifre."
	            );

	            List<Judecatori> lista = judecatorDaoImpl.afiseazaJudecatori();
	            request.setAttribute("listaJudecatori", lista);

	            request.getRequestDispatcher("tabela_judecatori.jsp")
	                   .forward(request, response);
	            return;
	        }

	        judecatorDaoImpl.modificaJudecator(
	            id1,
	            Nume_Judecator,
	            Prenume_Judecator,
	            CNP,
	            Data_Nasterii,
	            Grad
	        ); 

	        List<Judecatori> lista = judecatorDaoImpl.afiseazaJudecatori();
	        request.setAttribute("listaJudecatori", lista);
	        request.setAttribute(
	            "succes",
	            "✔️ Modificarea judecătorului a fost efectuată cu succes!"
	        );

	        request.getRequestDispatcher("tabela_judecatori.jsp")
	               .forward(request, response);
	        return;
	    }

	    if (request.getParameter("stergeJudecator") != null) { 
	        String idStr = request.getParameter("ID_Judecator");

	        if (idStr == null || idStr.isBlank()) {
	            request.setAttribute("eroare", "❌ Trebuie selectat un judecător pentru ștergere.");
	            RequestDispatcher rd = request.getRequestDispatcher("tabela_judecatori.jsp"); 
	            rd.forward(request, response); 
	            return;
	        }

	        int id2 = Integer.parseInt(idStr); 
	        judecator.setID_Judecator(id2); 
	        judecatorDaoImpl.stergeJudecator(judecator); 
	        List<Judecatori> lista = judecatorDaoImpl.afiseazaJudecatori();
	        request.setAttribute("listaJudecatori", lista);
	        request.setAttribute("succes", "✔️ Judecătorul a fost șters cu succes!");

	        request.getRequestDispatcher("tabela_judecatori.jsp").forward(request, response);
	        return;
	    } 
	    
	    if (request.getParameter("stergeJudecatoriSelectati") != null) {

	        String[] ids = request.getParameterValues("idStergere");

	        if (ids == null || ids.length == 0) {
	            request.setAttribute("eroare", "⚠️ Nu ai selectat niciun judecător!");
	        } else {
	            for (String id : ids) {
	                Judecatori j = new Judecatori();
	                j.setID_Judecator(Integer.parseInt(id));
	                judecatorDaoImpl.stergeJudecator(j);
	            }
	            request.setAttribute("succes", "✔️ Judecătorii selectați au fost șterși cu succes!");
	        }

	        List<Judecatori> lista = judecatorDaoImpl.afiseazaJudecatori();
	        request.setAttribute("listaJudecatori", lista);

	        RequestDispatcher rd =
	                request.getRequestDispatcher("tabela_judecatori.jsp");
	        rd.forward(request, response);
	        return;
	    }
	    
	    if (request.getParameter("stergeTotiJudecatorii") != null) {

	        judecatorDaoImpl.stergeTotiJudecatorii();

	        List<Judecatori> lista = judecatorDaoImpl.afiseazaJudecatori();
	        request.setAttribute("listaJudecatori", lista);
	        request.setAttribute("succes", "✔️ Toți judecătorii au fost șterși cu succes!");

	        RequestDispatcher rd =
	                request.getRequestDispatcher("tabela_judecatori.jsp");
	        rd.forward(request, response);
	        return;
	    }

	}


	public String getServletInfo() { 
		return "Short description"; 
	}
} 