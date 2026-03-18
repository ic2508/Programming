package Controller;

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
import pojo.Cazuri;
import DAOImpl.CazuriDaoImpl;
import DAOImpl.JudecatoriDaoImpl;
import DAOImpl.ProceseDaoImpl;
import DAOImpl.HibernateUtil;
import java.text.DateFormat;
import java.text.ParseException;


import java.text.SimpleDateFormat;
import java.util.Date;
import org.hibernate.Session;
import org.hibernate.Transaction;

public class CazuriController extends HttpServlet {

    CazuriDaoImpl cazuriDaoImpl = new CazuriDaoImpl();
    JudecatoriDaoImpl judecatoriDao = new JudecatoriDaoImpl();
    ProceseDaoImpl proceseDao = new ProceseDaoImpl();
    
    private void incarcaDateFormular(HttpServletRequest request) {
        List<Judecatori> listaJud = judecatoriDao.afiseazaJudecatori();
        List<Procese> listaProc = proceseDao.afiseazaProcese();

        request.setAttribute("listaJudecatori", listaJud);
        request.setAttribute("listaProcese", listaProc);
    }


    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        incarcaDateFormular(request);                
        RequestDispatcher rd = request.getRequestDispatcher("adauga_caz.jsp");
        rd.forward(request, response);
    }


    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        if (request.getParameter("adaugaCaz") != null) {

            Integer ID_Judecator = Integer.parseInt(request.getParameter("ID_Judecator"));
            Integer ID_Proces = Integer.parseInt(request.getParameter("ID_Proces"));
            
            if (cazuriDaoImpl.existaCombinatie(ID_Judecator, ID_Proces)) {
                request.setAttribute("eroare", "❌ Acest judecător are deja acest proces!");
                incarcaDateFormular(request);
                RequestDispatcher rd = request.getRequestDispatcher("adauga_caz.jsp");
                rd.forward(request, response);
                return;
            }
            
            Session session = HibernateUtil.getSessionFactory().openSession();
            Judecatori judecator = session.find(Judecatori.class, ID_Judecator);
            Procese proces = session.find(Procese.class, ID_Proces);

            DateFormat df = new SimpleDateFormat("yyyy-MM-dd");

            Cazuri cazuri = new Cazuri();
            cazuri.setJudecatori(judecator);
            cazuri.setProcese(proces);

            cazuriDaoImpl.adaugaCaz(cazuri);

            request.setAttribute("succes", "✔️ Cazul a fost adăugat cu succes!");

            incarcaDateFormular(request);

            request.getRequestDispatcher("adauga_caz.jsp").forward(request, response);
            return;
        }

        if (request.getParameter("afiseazaCazuri") != null) {
            List<Cazuri> listaCaz = new ArrayList();
            listaCaz = cazuriDaoImpl.afiseazaCazuri();
            request.setAttribute("listaCazuri", listaCaz);
            RequestDispatcher rd = request.getRequestDispatcher("tabela_cazuri.jsp");
            rd.forward(request, response);
        }

        if (request.getParameter("modificaCaz") != null) {

            String idCazParam = request.getParameter("ID_Caz");

            if (idCazParam == null || idCazParam.trim().isEmpty()) {
                request.setAttribute("eroare", "⚠️ Selectează un caz pentru modificare!");

                request.setAttribute("listaCazuri", cazuriDaoImpl.afiseazaCazuri());
                incarcaDateFormular(request);

                request.getRequestDispatcher("tabela_cazuri.jsp")
                       .forward(request, response);
                return;
            }

            Integer id1;
            try {
                id1 = Integer.parseInt(idCazParam);
            } catch (NumberFormatException e) {
                request.setAttribute("eroare", "❌ ID caz invalid!");

                request.setAttribute("listaCazuri", cazuriDaoImpl.afiseazaCazuri());
                incarcaDateFormular(request);

                request.getRequestDispatcher("tabela_cazuri.jsp")
                       .forward(request, response);
                return;
            }

            Integer ID_Judecator = Integer.parseInt(request.getParameter("ID_Judecator"));
            Integer ID_Proces = Integer.parseInt(request.getParameter("ID_Proces"));

            if (cazuriDaoImpl.existaCombinatie(ID_Judecator, ID_Proces)) {
                request.setAttribute("eroare", "❌ Combinația există deja!");

                request.setAttribute("listaCazuri", cazuriDaoImpl.afiseazaCazuri());
                incarcaDateFormular(request);

                request.getRequestDispatcher("tabela_cazuri.jsp")
                       .forward(request, response);
                return;
            }

            Session session = HibernateUtil.getSessionFactory().openSession();
            try {
                Judecatori judecator = session.find(Judecatori.class, ID_Judecator);
                Procese proces = session.find(Procese.class, ID_Proces);

                cazuriDaoImpl.modificaCaz(id1, judecator, proces);
            } finally {
                session.close();
            }

            request.setAttribute("listaCazuri", cazuriDaoImpl.afiseazaCazuri());
            incarcaDateFormular(request);
            request.setAttribute("succes", "✔️ Caz modificat cu succes!");

            request.getRequestDispatcher("tabela_cazuri.jsp")
                   .forward(request, response);
            return;
        }


        if (request.getParameter("stergeCaz") != null) {
            Integer id2 = Integer.parseInt(request.getParameter("ID_Caz"));
            cazuriDaoImpl.stergeCaz(id2);
            List<Cazuri> listaCaz = cazuriDaoImpl.afiseazaCazuri();
            request.setAttribute("listaCazuri", listaCaz);

            request.setAttribute("succes", "✔️ Cazul a fost șters cu succes!");

            RequestDispatcher rd = request.getRequestDispatcher("tabela_cazuri.jsp");
            rd.forward(request, response);
            return;
        }
        
        if (request.getParameter("stergeSelectate") != null) {

            String[] ids = request.getParameterValues("idStergere");

            if (ids == null || ids.length == 0) {
                request.setAttribute("eroare", "⚠️ Nu ai selectat niciun caz!");
            } else {
                for (String id : ids) {
                    cazuriDaoImpl.stergeCaz(Integer.parseInt(id));
                }
                request.setAttribute("succes", "✔️ Cazurile selectate au fost șterse!");
            }

            request.setAttribute("listaCazuri", cazuriDaoImpl.afiseazaCazuri());
            request.getRequestDispatcher("tabela_cazuri.jsp")
                   .forward(request, response);
            return;
        }

        
        if (request.getParameter("stergeTot") != null) {

            List<Cazuri> toate = cazuriDaoImpl.afiseazaCazuri();

            for (Cazuri c : toate) {
                cazuriDaoImpl.stergeCaz(c.getID_Caz());
            }

            request.setAttribute("listaCazuri", cazuriDaoImpl.afiseazaCazuri());
            request.setAttribute("succes", "✔️ Toate cazurile au fost șterse!");

            request.getRequestDispatcher("tabela_cazuri.jsp")
                   .forward(request, response);
            return;
        }
    }

    public String getServletInfo() {
        return "Short description";
    }
}
