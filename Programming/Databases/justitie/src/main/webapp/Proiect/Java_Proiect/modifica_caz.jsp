<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page language="java" import="java.lang.*,java.math.*,db.*,java.sql.*,java.util.*"%>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Modificare cazuri</title>
    <link rel="stylesheet" href="css/view.css?v=123">
</head>

<jsp:useBean id="jb" scope="session" class="db.JavaBean" />
<jsp:setProperty name="jb" property="*" />

<body class="page-justice">

    <div class="justice-card" style="width:95%; max-width:1500px;">

        <h1 class="justice-title">📑 Selectează cazul de modificat</h1>

        <br>

        <form action="m1_caz.jsp" method="post">

            <div style="overflow-x:auto;">

                <table class="justice-table">
                    <thead>
                        <tr>
                            <th></th>
                            <th>ID Caz</th>
                            <th>ID Judecător</th>
                            <th>Nume</th>
                            <th>Prenume</th>
                            <th>CNP</th>
                            <th>Data nașterii</th>
                            <th>Grad</th>
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
                        ResultSet rs = jb.vedeCaz();
                        long x;

                        while (rs.next()) {
                            x = rs.getInt("ID_Caz");
                    %>
                        <tr>
                            <td>
                                <input type="radio" name="primarykey" value="<%= x %>">
                            </td>
                            <td><%= x %></td>
                            <td><%= rs.getInt("ID_Judecator") %></td>
                            <td><%= rs.getString("Nume_Judecator") %></td>
                            <td><%= rs.getString("Prenume_Judecator") %></td>
                            <td><%= rs.getString("CNP") %></td>
                            <td><%= rs.getDate("Data_Nasterii") %></td>
                            <td><%= rs.getString("Grad") %></td>
                            <td><%= rs.getInt("ID_Proces") %></td>
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
            
            <div class="justice-nav-row">
             <button type="button"
            class="justice-btn success"
            onclick="location.href='nou_caz.jsp'">
        	➕ Adaugă un nou caz
    		</button>
    		
    		<button type="submit" class="justice-btn danger">
    			✏️ Modifică cazul selectat
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
