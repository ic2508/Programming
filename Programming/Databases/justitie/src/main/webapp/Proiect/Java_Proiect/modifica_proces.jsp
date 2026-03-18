<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page language="java" import="java.lang.*,java.math.*,db.*,java.sql.*,java.util.*"%>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Modificare procese</title>
    <link rel="stylesheet" href="css/view.css?v=123">
</head>

<jsp:useBean id="jb" scope="session" class="db.JavaBean" />
<jsp:setProperty name="jb" property="*" />

<body class="page-justice">

    <div class="justice-card" style="width:90%; max-width:1100px;">

        <h1 class="justice-title">📜 Selectează procesul de modificat</h1>

        <br>

        <form action="m1_proces.jsp" method="post">

            <div style="overflow-x:auto;">

                <table class="justice-table">
                    <thead>
                        <tr>
                            <th></th>
                            <th>ID Proces</th>
                            <th>Număr dosar</th>
                            <th>Tip proces</th>
                            <th>Stadiu</th>
                            <th>Data înregistrării</th>
                            <th>Denumire</th>
                        </tr>
                    </thead>

                    <tbody>
                    <%
                        jb.connect();
                        ResultSet rs = jb.vedeTabela("Procese");
                        long x;

                        while (rs.next()) {
                            x = rs.getLong("ID_Proces");
                    %>
                        <tr>
                            <td>
                                <input type="radio" name="primarykey" value="<%= x %>">
                            </td>
                            <td><%= x %></td>
                            <td><%= rs.getString("Numar_Dosar") %></td>
                            <td><%= rs.getString("Tip_Proces") %></td>
                            <td><%= rs.getString("Stadiu") %></td>
                            <td><%= rs.getDate("Data_Inregistrarii") %></td>
                            <td><%= rs.getString("Denumire") %></td>
                        </tr>
                    <%
                        }
                        rs.close();
                        jb.disconnect();
                    %>
                    </tbody>
                </table>

            </div>
			
			<br>
			
			<div class="justice-nav-row">
            <button type="button"
            class="justice-btn success"
            onclick="location.href='nou_proces.jsp'">
        	➕ Adaugă un nou proces
    		</button>
    		
    		<button type="submit" class="justice-btn danger">
    			✏️ Modifică procesul selectat
			</button>

    		<button type="button"
            class="justice-btn secondary"
            onclick="location.href='index.html'">
        	🏠 Acasă
    		</button>
        </div>
            

        </form>

    </div>

</body>
</html>
