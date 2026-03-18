<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page language="java" import="db.*,java.sql.*,java.util.*"%>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Adaugă caz</title>
    <link rel="stylesheet" href="css/view.css?v=123">
</head>

<jsp:useBean id="jb" scope="session" class="db.JavaBean" />

<body class="page-justice">

<div class="justice-card" style="width:480px;">

<%
    String id1 = request.getParameter("ID_Judecator");
    String id2 = request.getParameter("ID_Proces");

    if (id1 != null && id2 != null) {

        int jud = Integer.parseInt(id1);
        int proc = Integer.parseInt(id2);

        jb.connect();

        try {
            if (jb.existaCaz(jud, proc)) {
%>
                <h2 class="justice-title" style="color:#c0392b;">
                    ❌ Caz deja existent
                </h2>

                <p>
                    Există deja un caz cu judecătorul și procesul selectat!
                </p>

                <button type="button"
        	class="justice-btn secondary"
        	onclick="location.href='nou_caz.jsp'">
    		⬅️ Înapoi
			</button>
<%
            } else {
                jb.adaugaCaz(jud, proc);
%>
                <h2 class="justice-title" style="color:#27ae60;">
                    ✅ Caz adăugat cu succes
                </h2>

                <p>
                    Cazul a fost adăugat în baza de date!
                </p>

                <button type="button"
        	class="justice-btn secondary"
        	onclick="location.href='tabela_cazuri.jsp'">
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
                Combinația Judecător – Proces există deja sau datele sunt invalide!
            </p>

            <button type="button"
        	class="justice-btn secondary"
        	onclick="location.href='nou_caz.jsp'">
    		⬅️ Înapoi
			</button>
<%
        }

        jb.disconnect();

    } else {
        jb.connect();
        ResultSet rs1 = jb.vedeTabela("Judecatori");
        ResultSet rs2 = jb.vedeTabela("Procese");
%>

        <h2 class="justice-title">⚖️ Adaugă caz ⚖️</h2>

        <form action="nou_caz.jsp" method="post">

            <label><b>Selectează judecătorul:</b></label>
            <select name="ID_Judecator" class="justice-btn" required>
                <option value="">-- Alege judecător --</option>
                <%
                    while (rs1.next()) {
                %>
                    <option value="<%= rs1.getInt("ID_Judecator") %>">
                        <%= rs1.getInt("ID_Judecator") %> –
                        <%= rs1.getString("Nume_Judecator") %>
                        <%= rs1.getString("Prenume_Judecator") %>
                        (CNP: <%= rs1.getString("CNP") %>)
                    </option>
                <%
                    }
                %>
            </select>

            <br><br>

            <label><b>Selectează procesul:</b></label>
            <select name="ID_Proces" class="justice-btn" required>
                <option value="">-- Alege proces --</option>
                <%
                    while (rs2.next()) {
                %>
                    <option value="<%= rs2.getInt("ID_Proces") %>">
                        <%= rs2.getInt("ID_Proces") %> –
                        <%= rs2.getString("Numar_Dosar") %>,
                        <%= rs2.getString("Tip_Proces") %>,
                        <%= rs2.getString("Stadiu") %>
                    </option>
                <%
                    }
                    rs1.close();
                    rs2.close();
                    jb.disconnect();
                %>
            </select>

           
			<br>
			
            <button type="submit" class="justice-btn success">
    			➕ Adaugă caz
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
