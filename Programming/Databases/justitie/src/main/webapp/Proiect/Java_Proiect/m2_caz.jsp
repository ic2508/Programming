<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page language="java" import="db.*,java.sql.*"%>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Modificare caz</title>
    <link rel="stylesheet" href="css/view.css?v=123">
</head>

<jsp:useBean id="jb" scope="session" class="db.JavaBean" />

<body class="page-justice">

<div class="justice-card" style="width:480px;">

<%
    // 🔒 PROTECȚIE: dacă pagina e accesată direct
    String sIdCaz = request.getParameter("ID_Caz");
    String sIdJud = request.getParameter("ID_Judecator");
    String sIdProc = request.getParameter("ID_Proces");

    if (sIdCaz == null || sIdJud == null || sIdProc == null) {
        response.sendRedirect("modifica_caz.jsp.jsp");
        return;
    }

    int idCaz = Integer.parseInt(sIdCaz);
    int idJud = Integer.parseInt(sIdJud);
    int idProc = Integer.parseInt(sIdProc);

    jb.connect();

    try {
        if (jb.existaCazLaModificare(idCaz, idJud, idProc)) {
%>
            <h2 class="justice-title" style="color:#c0392b;">
                ❌ Modificare invalidă
            </h2>

            <p>
                Există deja un alt caz cu judecătorul și procesul selectat!
            </p>

            <button type="button"
        	class="justice-btn secondary"
        	onclick="history.back()">
    		⬅️ Înapoi la tabel
			</button>
<%
        } else {
            String[] valori = {
                String.valueOf(idJud),
                String.valueOf(idProc)
            };
            String[] campuri = {
                "ID_Judecator",
                "ID_Proces"
            };

            jb.modificaTabela("Cazuri", "ID_Caz", idCaz, campuri, valori);
%>
            <h2 class="justice-title" style="color:#27ae60;">
                ✅ Modificare reușită
            </h2>

            <p>
                Modificările au fost efectuate cu succes!
            </p>

            <button type="button"
        	class="justice-btn secondary"
        	onclick="history.back()">
    		⬅️ Înapoi la tabel
			</button>
<%
        }
    } catch (SQLException e) {
%>
        <h2 class="justice-title" style="color:#c0392b;">
            ❌ Eroare
        </h2>

        <p>
            A apărut o eroare la modificarea cazului!
        </p>

        <button type="button"
        	class="justice-btn secondary"
        	onclick="history.back()">
    		⬅️ Înapoi la tabel
			</button>
<%
    }

    jb.disconnect();
%>

</div>

</body>
</html>
