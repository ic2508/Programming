<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page language="java" import="db.*,java.sql.*"%>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Ștergere procese</title>
    <link rel="stylesheet" href="css/view.css?v=123">
</head>

<jsp:useBean id="jb" scope="session" class="db.JavaBean" />

<body class="page-justice">

    <div class="justice-card" style="width: 420px;">

        <%
            String[] s = request.getParameterValues("primarykey");

            if (s == null || s.length == 0) {
        %>
            <h2 class="justice-title" style="color:#c0392b;">
                ❌ Niciun proces selectat
            </h2>

            <p>
                Nu ai selectat niciun proces pentru ștergere!
            </p>

            <button type="button"
        	class="justice-btn secondary"
        	onclick="location.href='tabela_procese.jsp'">
    		⬅️ Înapoi la tabel
			</button>

        <%
            } else {
                try {
                    jb.connect();
                    jb.stergeDateTabela(s, "Procese", "ID_Proces");
                    jb.disconnect();
        %>
                    <h2 class="justice-title" style="color:#27ae60;">
                        ✅ Ștergere reușită
                    </h2>

                    <p>
                        Procesele selectate au fost șterse cu succes!
                    </p>

                    <button type="button"
        	class="justice-btn secondary"
        	onclick="location.href='tabela_procese.jsp'">
    		⬅️ Înapoi la tabel
			</button>

        <%
                } catch (Exception e) {
        %>
                    <h2 class="justice-title" style="color:#c0392b;">
                        ❌ Eroare la ștergere
                    </h2>

                    <p>
                        <%= e.getMessage() %>
                    </p>

                    <button type="button"
        	class="justice-btn secondary"
        	onclick="location.href='tabela_procese.jsp'">
    		⬅️ Înapoi la tabel
			</button>
        <%
                }
            }
        %>

    </div>

</body>
</html>
