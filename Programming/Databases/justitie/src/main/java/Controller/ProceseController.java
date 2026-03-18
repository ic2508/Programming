package Controller; 

import DAO.ProceseDao; 
import java.io.IOException; 
import java.util.ArrayList; 
import java.util.List; 
import jakarta.servlet.RequestDispatcher; 
import jakarta.servlet.ServletException; 
import jakarta.servlet.http.HttpServlet; 
import jakarta.servlet.http.HttpServletRequest; 
import jakarta.servlet.http.HttpServletResponse; 
import pojo.Procese; 
import DAOImpl.ProceseDaoImpl; 

public class ProceseController extends HttpServlet { 

	Procese proces = new Procese(); 
	ProceseDaoImpl procesDaoImpl = new ProceseDaoImpl(); 

	protected void doGet(HttpServletRequest request, HttpServletResponse response) 
			throws ServletException, IOException { 
		if (request.getParameter("adaugaProces") != null) { 

		    String Numar_Dosar = request.getParameter("Numar_Dosar"); 
		    String Tip_Proces = request.getParameter("Tip_Proces"); 
		    String Stadiu = request.getParameter("Stadiu"); 
		    String Data_Inregistrarii = request.getParameter("Data_Inregistrarii");
		    String Denumire = request.getParameter("Denumire");

		    if (Numar_Dosar == null || Numar_Dosar.isBlank() ||
		        Tip_Proces == null || Tip_Proces.isBlank() ||
		        Stadiu == null || Stadiu.isBlank() ||
		        Data_Inregistrarii == null || Data_Inregistrarii.isBlank() ||
		        Denumire == null || Denumire.isBlank()) {

		        request.setAttribute(
		            "eroare",
		            "❌ Toate câmpurile sunt obligatorii pentru adăugarea unui proces!"
		        );
		        request.getRequestDispatcher("adauga_proces.jsp")
		               .forward(request, response);
		        return;
		    }

		    if (!Numar_Dosar.matches("\\d{4}/\\d{4}")) {
		        request.setAttribute(
		            "eroare",
		            "❌ Numărul dosarului trebuie să aibă formatul xxxx/xxxx"
		        );
		        request.getRequestDispatcher("adauga_proces.jsp")
		               .forward(request, response);
		        return;
		    }

		    java.sql.Date dataSQL;
		    try {
		        dataSQL = java.sql.Date.valueOf(Data_Inregistrarii);
		    } catch (IllegalArgumentException e) {
		        request.setAttribute(
		            "eroare",
		            "❌ Data înregistrării trebuie să fie în formatul yyyy-MM-dd!"
		        );
		        request.getRequestDispatcher("adauga_proces.jsp")
		               .forward(request, response);
		        return;
		    }

		    Procese proces = new Procese();
		    proces.setNumar_Dosar(Numar_Dosar);
		    proces.setTip_Proces(Tip_Proces);
		    proces.setStadiu(Stadiu);
		    proces.setData_Inregistrarii(dataSQL);
		    proces.setDenumire(Denumire);

		    procesDaoImpl.adaugaProces(proces);

		    request.setAttribute(
		        "succes",
		        "✔️ Procesul a fost adăugat cu succes!"
		    );
		    request.getRequestDispatcher("adauga_proces.jsp")
		           .forward(request, response);
		    return;
		}

	} 

	protected void doPost(HttpServletRequest request, HttpServletResponse response) 
			throws ServletException, IOException { 
		if (request.getParameter("afiseazaProcese") != null) { 



			List<Procese> listaProcese = new ArrayList(); 
			listaProcese = procesDaoImpl.afiseazaProcese(); 
			request.setAttribute("listaProcese", listaProcese); 
			RequestDispatcher rd = request.getRequestDispatcher("tabela_procese.jsp"); 
			rd.forward(request, response); 
		} 

		if (request.getParameter("modificaProces") != null) {

		    String idStr = request.getParameter("ID_Proces");

		    if (idStr == null || idStr.isBlank()) {
		        request.setAttribute("eroare", "❌ Trebuie selectat un proces pentru modificare!");
		        request.setAttribute("listaProcese", procesDaoImpl.afiseazaProcese());
		        request.getRequestDispatcher("tabela_procese.jsp")
		               .forward(request, response);
		        return;
		    }

		    int id1 = Integer.parseInt(idStr);

		    String Numar_Dosar = request.getParameter("Numar_Dosar");
		    String Tip_Proces = request.getParameter("Tip_Proces");
		    String Stadiu = request.getParameter("Stadiu");
		    String Data_Inregistrarii = request.getParameter("Data_Inregistrarii");
		    String Denumire = request.getParameter("Denumire");

		    if (Numar_Dosar == null || !Numar_Dosar.matches("\\d{4}/\\d{4}")) {
		        request.setAttribute(
		            "eroare",
		            "❌ Numărul dosarului trebuie să aibă formatul xxxx/xxxx"
		        );

		        request.setAttribute("listaProcese", procesDaoImpl.afiseazaProcese());
		        request.getRequestDispatcher("tabela_procese.jsp")
		               .forward(request, response);
		        return;
		    }

		    procesDaoImpl.modificaProces(
		        id1,
		        Numar_Dosar,
		        Tip_Proces,
		        Stadiu,
		        Data_Inregistrarii,
		        Denumire
		    ); 

		    List<Procese> lista = procesDaoImpl.afiseazaProcese();
		    request.setAttribute("listaProcese", lista);
		    request.setAttribute(
		        "succes",
		        "✔️ Procesul a fost modificat cu succes!"
		    );

		    request.getRequestDispatcher("tabela_procese.jsp")
		           .forward(request, response);
		    return;
		}


		if (request.getParameter("stergeProces") != null) { 
			int id2 = Integer.parseInt(request.getParameter("ID_Proces")); 
			proces.setID_Proces(id2); 
			procesDaoImpl.stergeProces(proces); 
			
			List<Procese> lista = procesDaoImpl.afiseazaProcese();
		    request.setAttribute("listaProcese", lista);
		    request.setAttribute("succes", "✔️ Procesul a fost șters cu succes!");

		    request.getRequestDispatcher("tabela_procese.jsp").forward(request, response);
		    return;
		} 
		
		if (request.getParameter("stergeProceseSelectate") != null) {

		    String[] ids = request.getParameterValues("idStergere");

		    if (ids == null || ids.length == 0) {
		        request.setAttribute("eroare", "⚠️ Nu ai selectat niciun proces!");
		    } else {
		        for (String id : ids) {
		            Procese p = new Procese();
		            p.setID_Proces(Integer.parseInt(id));
		            procesDaoImpl.stergeProces(p);
		        }
		        request.setAttribute("succes", "✔️ Procesele selectate au fost șterse cu succes!");
		    }

		    List<Procese> lista = procesDaoImpl.afiseazaProcese();
		    request.setAttribute("listaProcese", lista);

		    RequestDispatcher rd =
		            request.getRequestDispatcher("tabela_procese.jsp");
		    rd.forward(request, response);
		    return;
		}

        if (request.getParameter("stergeToateProcesele") != null) {

            procesDaoImpl.stergeToateProcesele();

            request.setAttribute("listaProcese", procesDaoImpl.afiseazaProcese());
            request.setAttribute("succes", "✔️ Toate procesele au fost șterse!");

            request.getRequestDispatcher("tabela_procese.jsp")
                   .forward(request, response);
        }
    }

 
	public String getServletInfo() { 
		return "Short description"; 
	}
} 