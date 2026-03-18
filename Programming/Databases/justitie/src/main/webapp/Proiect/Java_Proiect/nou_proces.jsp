<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page language="java" import="db.*,java.sql.*"%>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Adaugă proces</title>
    <link rel="stylesheet" href="css/view.css?v=123">
</head>

<jsp:useBean id="jb" scope="session" class="db.JavaBean" />

<body class="page-justice">

<div class="justice-card" style="width:480px;">

<%
    String numarDosar = request.getParameter("Numar_Dosar");
    String tip = request.getParameter("Tip_Proces");
    String stadiu = request.getParameter("Stadiu");
    String data = request.getParameter("Data_Inregistrarii");
    String denumire = request.getParameter("Denumire");

    if (numarDosar != null) {

        jb.connect();

        try {
            if (jb.existaProces(numarDosar)) {
%>
                <h2 class="justice-title" style="color:#c0392b;">
                    ❌ Număr de dosar existent
                </h2>

                <p>
                    Există deja un proces cu acest număr de dosar!
                </p>

                <button type="button"
        	class="justice-btn secondary"
        	onclick="location.href='nou_proces.jsp'">
    		⬅️ Înapoi
			</button>
<%
            } else {
                jb.adaugaProces(numarDosar, tip, stadiu, data, denumire);
%>
                <h2 class="justice-title" style="color:#27ae60;">
                    ✅ Proces adăugat
                </h2>

                <p>
                    Procesul a fost adăugat cu succes!
                </p>

                 <button type="button"
        	class="justice-btn secondary"
        	onclick="location.href='tabela_procese.jsp'">
    		⬅️ Înapoi la tabel
			</button>
<%
            }
        } catch (SQLException e) {
%>
            <h2 class="justice-title" style="color:#c0392b;">
                ❌ Eroare la adăugare
            </h2>

            <p>
                Datele introduse sunt invalide sau numărul de dosar există deja!
            </p>

            <button type="button"
        	class="justice-btn secondary"
        	onclick="location.href='nou_proces.jsp'">
    		⬅️ Înapoi
			</button>
<%
        }

        jb.disconnect();

    } else {
%>

        <h2 class="justice-title">⚖️ Adaugă proces ⚖️</h2>

        <form action="nou_proces.jsp" method="post">

            <label>Număr dosar:</label>
				<input type="text"
      			 name="Numar_Dosar"
       			class="justice-btn"
       			pattern="[0-9]{4}/[0-9]{4}"
       			title="Format obligatoriu: xxxx/xxxx"
       			required>

            <br><br>

            <label>Tip proces:</label>
            <input type="text" name="Tip_Proces" class="justice-btn" required>

            <br><br>

            <label>Stadiu:</label>
            <input type="text" name="Stadiu" class="justice-btn" required>

            <br><br>

            <label>Data înregistrării:</label>
            <input type="date" name="Data_Inregistrarii" class="justice-btn" required>

            <br><br>

            <label>Denumire:</label>
            <input type="text" name="Denumire" class="justice-btn" required>

            <br>

            <button type="submit" class="justice-btn success">
    			➕ Adaugă judecător
			</button>


        </form>


        <div class="justice-nav-row">
            <button type="button"
        	class="justice-btn secondary"
        	onclick="history.back()">
    		⬅️ Înapoi la tabel
			</button>

    		<button type="button"
            class="justice-btn secondary"
            onclick="location.href='index.html'">
        	🏠 Acasă
    		</button>
        </div>

<%
    }
%>

</div>

</body>
</html>
