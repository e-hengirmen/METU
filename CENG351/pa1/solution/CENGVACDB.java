package ceng.ceng351.cengvacdb;

import java.sql.*;

public class CENGVACDB implements ICENGVACDB{

    private static String user = "e2468015"; // TODO: Your userName
    private static String password = "f#+syX6qp4Qe"; //  TODO: Your password
    private static String host = "144.122.71.121"; // host name
    private static String database = "db2468015"; // TODO: Your database name
    private static int port = 8080; // port

    private static Connection connection = null;

    /*
    CREATE TABLE IF NOT EXISTS `User` ( `userID` INT NOT NULL , `userName` VARCHAR(30) NOT NULL,`age` INT NOT NULL,`address` VARCHAR(150) NOT NULL , PRIMARY KEY (`userID`));
    CREATE TABLE IF NOT EXISTS `Vaccine` ( `code` INT NOT NULL , `vaccinename` VARCHAR(30) NOT NULL,`type` VARCHAR(30) NOT NULL , PRIMARY KEY (`code`));
    CREATE TABLE IF NOT EXISTS `Vaccination` ( `code` INT NOT NULL , `userID` INT NOT NULL ,`dose` INT NOT NULL ,`vacdate` DATE NOT NULL , FOREIGN KEY(`code`) REFERENCES `Vaccine`(`code`),FOREIGN KEY(`userID`) REFERENCES `User`(`userID`), PRIMARY KEY (`code`,`userID`,`dose`));
    CREATE TABLE IF NOT EXISTS `AllergicSideEffect` ( `effectcode` INT NOT NULL , `effectname` VARCHAR(50) NOT NULL, PRIMARY KEY (`effectcode`));
    CREATE TABLE IF NOT EXISTS `Seen` ( `effectcode` INT NOT NULL , `code` INT NOT NULL , `userID` INT NOT NULL , `date` DATE NOT NULL ,`degree` VARCHAR(30) NOT NULL, FOREIGN KEY(`effectcode`) REFERENCES `AllergicSideEffect`(`effectcode`), FOREIGN KEY(`code`) REFERENCES `Vaccine`(`code`),FOREIGN KEY(`userID`) REFERENCES `User`(`userID`),PRIMARY KEY (`effectcode`, `code` , `userID`))


     */





    @Override
    public void initialize() {
        String url = "jdbc:mysql://" + host + ":" + port + "/" + database + "?useSSL=false";

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection =  DriverManager.getConnection(url, user, password);
        }
        catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        }
        dropTables();
    }

    @Override
    public int createTables() {
        int res=0;
        String[] cTables = {
                "CREATE TABLE IF NOT EXISTS `User` ( `userID` INT NOT NULL , `userName` VARCHAR(30) NOT NULL,`age` INT NOT NULL,`address` VARCHAR(150) NOT NULL, `password` VARCHAR(30) NOT NULL ,`status` VARCHAR(15) NOT NULL , PRIMARY KEY (`userID`));",
                "CREATE TABLE IF NOT EXISTS `Vaccine` ( `code` INT NOT NULL , `vaccinename` VARCHAR(30) NOT NULL,`type` VARCHAR(30) NOT NULL , PRIMARY KEY (`code`));",
                "CREATE TABLE IF NOT EXISTS `Vaccination` ( `code` INT NOT NULL , `userID` INT NOT NULL ,`dose` INT NOT NULL ,`vacdate` DATE NOT NULL , FOREIGN KEY(`code`) REFERENCES `Vaccine`(`code`) ON DELETE CASCADE,FOREIGN KEY(`userID`) REFERENCES `User`(`userID`), PRIMARY KEY (`code`,`userID`,`dose`));",
                "CREATE TABLE IF NOT EXISTS `AllergicSideEffect` ( `effectcode` INT NOT NULL , `effectname` VARCHAR(50) NOT NULL, PRIMARY KEY (`effectcode`));",
                "CREATE TABLE IF NOT EXISTS `Seen` ( `effectcode` INT NOT NULL , `code` INT NOT NULL , `userID` INT NOT NULL , `date` DATE NOT NULL ,`degree` VARCHAR(30) NOT NULL, FOREIGN KEY(`effectcode`) REFERENCES `AllergicSideEffect`(`effectcode`), FOREIGN KEY(`code`) REFERENCES `Vaccine`(`code`) ON DELETE CASCADE,FOREIGN KEY(`userID`) REFERENCES `User`(`userID`),PRIMARY KEY (`effectcode`, `code` , `userID`));"
        };

        for(String s:cTables) {
            try {
                Statement statement = connection.createStatement();
                statement.executeUpdate(s);
                res++;
                statement.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }



        return res;
    }

    @Override
    public int dropTables() {
        int res = 0;
        String[] tableNames = {"Seen", "Vaccination", "User", "Vaccine", "AllergicSideEffect"};
        String queryDropTable = "DROP TABLE IF EXISTS `";

        for(String s:tableNames) {
            try {
                Statement statement = this.connection.createStatement();
                statement.executeUpdate("DROP TABLE IF EXISTS `" + s + "`;");
                res++;
                statement.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return res;
    }



    /**
     * Should insert an array of User into the database.
     *
     * @return Number of rows inserted successfully.
     */
    @Override
    public int insertUser(User[] users) {
        int res=0;

        for(User u:users){
            try {
                Statement statement = this.connection.createStatement();
                statement.executeUpdate("INSERT INTO `User` VALUES ("+u.getUserID()+",\""+u.getUserName()+"\","+u.getAge()+",\""+u.getAddress()+"\",\""+u.getPassword()+"\",\""+u.getStatus()+"\");");
                res++;
            }
            catch (SQLException e){
                e.printStackTrace();
            }
        }



        return res;
    }

    /**
     * Should insert an array of AllergicSideEffect into the database.
     *
     * @return Number of rows inserted successfully.
     */
    @Override
    public int insertAllergicSideEffect(AllergicSideEffect[] sideEffects) {
        int res=0;

        for(AllergicSideEffect se:sideEffects){
            try {
                Statement statement = this.connection.createStatement();
                statement.executeUpdate("INSERT INTO `AllergicSideEffect` VALUES ("+se.getEffectCode()+",\""+se.getEffectName()+"\");");
                res++;
            }
            catch (SQLException e){
                e.printStackTrace();
            }
        }



        return res;
    }

    @Override
    public int insertVaccine(Vaccine[] vaccines) {
        int res=0;

        for(Vaccine v:vaccines){
            try {
                Statement statement = this.connection.createStatement();
                statement.executeUpdate("INSERT INTO `Vaccine` VALUES ("+v.getCode()+",\""+v.getVaccineName()+"\",\""+v.getType()+"\");");
                res++;
            }
            catch (SQLException e){
                e.printStackTrace();
            }
        }



        return res;
    }

    @Override
    public int insertVaccination(Vaccination[] vaccinations) {
        int res=0;

        for(Vaccination v:vaccinations){
            try {
                Statement statement = this.connection.createStatement();
                //System.out.println("INSERT INTO `Vaccination` VALUES ("+v.getCode()+","+v.getUserID()+","+v.getDose()+",`"+v.getVacdate()+"`);");
                statement.executeUpdate("INSERT INTO `Vaccination` VALUES ("+v.getCode()+","+v.getUserID()+","+v.getDose()+",\""+v.getVacdate()+"\");");
                res++;
            }
            catch (SQLException e){
                e.printStackTrace();
            }
        }



        return res;
    }

    @Override
    public int insertSeen(Seen[] seens) {
        int res=0;

        for(Seen s:seens){
            try {
                Statement statement = this.connection.createStatement();
                statement.executeUpdate("INSERT INTO `Seen` VALUES ("+s.getEffectcode()+","+s.getCode()+","+s.getUserID()+",\""+s.getDate()+"\",\""+s.getDegree()+"\");");
                res++;
            }
            catch (SQLException e){
                e.printStackTrace();
            }
        }



        return res;
    }



    /**
     * Should return vaccines that have not been applied to any user
     *
     * @return Vaccine[]
     */
    @Override
    public Vaccine[] getVaccinesNotAppliedAnyUser() {
        try{
            String qnum="select count(*) from Vaccine V where V.code not in (select O.code from Vaccination O);";
            Statement statement = this.connection.createStatement();
            ResultSet rsnum=statement.executeQuery(qnum);
            rsnum.next();
            int x=rsnum.getInt(1);

            Vaccine[] arr=new Vaccine[x];
            String q="select code,vaccinename,type from Vaccine V where V.code not in (select O.code from Vaccination O) order by V.code asc;";
            ResultSet rs=statement.executeQuery(q);
            int i=0;
            while(rs.next()){
                arr[i]=new Vaccine(rs.getInt(1),rs.getString(2),rs.getString(3));

                //arr[i].setCode(rs.getInt(1));
                //arr[i].setVaccineName(rs.getString(2));
                //arr[i].setType(rs.getString(3));
                //System.out.println(rs.getString(3)+rs.getString(2)+rs.getInt(1));
                //System.out.println(arr[i].getType()+arr[i].getVaccineName()+arr[i].getCode());

                i++;
            }






            return arr;
        }
        catch (SQLException e){
            e.printStackTrace();
        }

        return new Vaccine[0];
    }





    /**
     * Should return the users who have been vaccinated for two doses since the
     * given date
     *
     * @return UserIDuserNameAddressResult[]
     */
    @Override
    public QueryResult.UserIDuserNameAddressResult[] getVaccinatedUsersforTwoDosesByDate(String vacdate) {
        String q="select U.userID, U.userName, U.address from Vaccination V1,Vaccination V2,User U where V1.userID=U.userID and V1.userID=V2.userID and V1.dose=1 and V2.dose=2 and V1.vacdate>=\""+vacdate+"\" and V2.vacdate>=\""+vacdate+"\" order by U.userID asc;";
        String qnum="select count(*) from Vaccination V1,Vaccination V2,User U where V1.userID=U.userID and V1.userID=V2.userID and V1.dose=1 and V2.dose=2 and V1.vacdate>=\""+vacdate+"\" and V2.vacdate>=\""+vacdate+"\";";
        try {
            Statement statement = this.connection.createStatement();
            ResultSet rsnum=statement.executeQuery(qnum);
            rsnum.next();
            int num=rsnum.getInt(1);

            QueryResult.UserIDuserNameAddressResult[] arr=new QueryResult.UserIDuserNameAddressResult[num];
            ResultSet rs=statement.executeQuery(q);
            int i=0;
            while(rs.next()){
                arr[i]=new QueryResult.UserIDuserNameAddressResult(""+rs.getInt(1),rs.getString(2),rs.getString(3));
                i++;
            }

            return arr;
        }
        catch (SQLException e){
            e.printStackTrace();
        }





        return new QueryResult.UserIDuserNameAddressResult[0];
    }




    /**
     * List of the two recent vaccines applied to any user that
     * do not contain ‘vac’ in their name
     *
     * @return Vaccine[]
     */
    @Override
    public Vaccine[] getTwoRecentVaccinesDoNotContainVac() {
        String q="select B.code,B.vaccinename,B.type,max(A.vacdate) from Vaccination A,Vaccine B where A.code=B.code and vaccinename not like \"%vac%\" group by B.code,B.vaccinename,B.type order by max(A.vacdate) desc;";
        String qnum="select count(*) from Vaccination A,Vaccine B where A.code=B.code and vaccinename not like \"%vac%\" group by B.code,B.vaccinename,B.type order by max(A.vacdate) desc;";

        try {
            Statement statement = this.connection.createStatement();
            ResultSet rsnum=statement.executeQuery(qnum);
            rsnum.next();
            int num=rsnum.getInt(1);
            if(num>2)num=2;

            if(num==0)return new Vaccine[0];
            Vaccine[] arr=new Vaccine[num];
            ResultSet rs=statement.executeQuery(q);

            rs.next();
            Vaccine temp=new Vaccine(rs.getInt(1),rs.getString(2),rs.getString(3));
            int code0=rs.getInt(1);
            if(num==1){
                arr[0]=new Vaccine(rs.getInt(1),rs.getString(2),rs.getString(3));
                return arr;
            }
            rs.next();
            int code1=rs.getInt(1);
            if(code0<code1){
                arr[0]=new Vaccine(temp.getCode(),temp.getVaccineName(),temp.getType());
                arr[1]=new Vaccine(rs.getInt(1),rs.getString(2),rs.getString(3));
            }
            else{
                arr[1]=new Vaccine(temp.getCode(),temp.getVaccineName(),temp.getType());
                arr[0]=new Vaccine(rs.getInt(1),rs.getString(2),rs.getString(3));
            }


            return arr;
        }
        catch (SQLException e){
            e.printStackTrace();
        }


        return new Vaccine[0];
    }




    @Override
    public QueryResult.UserIDuserNameAddressResult[] getUsersAtHasLeastTwoDoseAtMostOneSideEffect() {
        String q="select U.userID,userName,address from User U,Vaccination V where V.userID=U.userID group by U.userID,userName,address having count(*)>=2 and U.userID in (select U.userID from User U,Seen S where S.userID=U.userID group by U.userID,userName,address having count(*)=1 union select userID from User U where not exists (select S.userId from Seen S where S.userID=U.userID)) order by userID;";
        String qnum="select count(*) from (select count(*) from User U,Vaccination V where V.userID=U.userID group by U.userID,userName,address having count(*)>=2 and U.userID in (select U.userID from User U,Seen S where S.userID=U.userID group by U.userID,userName,address having count(*)=1 union select userID from User U where not exists (select S.userId from Seen S where S.userID=U.userID))) as T;";

        try{
            Statement statement = this.connection.createStatement();
            ResultSet rsnum=statement.executeQuery(qnum);
            rsnum.next();
            int num=rsnum.getInt(1);

            QueryResult.UserIDuserNameAddressResult[] arr=new QueryResult.UserIDuserNameAddressResult[num];

            ResultSet rs=statement.executeQuery(q);
            int i=0;
            while(rs.next()){
                arr[i]=new QueryResult.UserIDuserNameAddressResult(""+rs.getInt(1),rs.getString(2),rs.getString(3));
                i++;
            }
            return arr;
        }
        catch (SQLException e){
            e.printStackTrace();
        }




        return new QueryResult.UserIDuserNameAddressResult[0];
    }




    //List users who have been vaccinated with all vaccines that
    //can cause the given side effect (10 pts)
    @Override
    public QueryResult.UserIDuserNameAddressResult[] getVaccinatedUsersWithAllVaccinesCanCauseGivenSideEffect(String effectname) {
        String q="select U.userID,userName,address from User U where not exists(Select V.code from Vaccine V, AllergicSideEffect A,Seen S where V.code=S.code and A.effectcode=S.effectcode and A.effectname=\""+effectname+"\" and not exists(Select * from Vaccination Vvv where U.userID=Vvv.userID and V.code=Vvv.code))order by userID;";
        String qnum="select count(*) from User U where not exists(Select V.code from Vaccine V, AllergicSideEffect A,Seen S where V.code=S.code and A.effectcode=S.effectcode and A.effectname=\""+effectname+"\" and not exists(Select * from Vaccination Vvv where U.userID=Vvv.userID and V.code=Vvv.code))order by userID;";

        try {
            Statement statement = this.connection.createStatement();
            ResultSet rsnum = statement.executeQuery(qnum);
            rsnum.next();
            int num = rsnum.getInt(1);

            QueryResult.UserIDuserNameAddressResult[] arr=new QueryResult.UserIDuserNameAddressResult[num];

            ResultSet rs=statement.executeQuery(q);
            int i=0;
            while(rs.next()){
                arr[i]=new QueryResult.UserIDuserNameAddressResult(""+rs.getInt(1),rs.getString(2),rs.getString(3));
                i++;
            }
            return arr;
        }
        catch (SQLException e){
            e.printStackTrace();
        }



        return new QueryResult.UserIDuserNameAddressResult[0];
    }





    /*
    List users who have been vaccinated with at least two dif-
    ferent types of vaccines within the given time interval

    You should include dateStart and dateEnd in the result, it is a CLOSED interval.
            Input: startDate, endDate
    Output: userID, userName, address
    Order the results by userID in ascending order
    */

    @Override
    public QueryResult.UserIDuserNameAddressResult[] getUsersWithAtLeastTwoDifferentVaccineTypeByGivenInterval(String startdate, String enddate) {
        String q="select distinct U.userID, userName, address from User U,Vaccination V1,Vaccination V2 where V1.vacdate>=\""+startdate+"\" and V1.vacdate<=\""+enddate+"\" and V2.vacdate>=\""+startdate+"\" and V2.vacdate<=\""+enddate+"\" and V1.code!=V2.code and V1.userID=V2.userID and V1.userID=U.userID";
        String qnum="select count(*) from(select distinct U.userID from User U,Vaccination V1,Vaccination V2 where V1.vacdate>=\""+startdate+"\" and V1.vacdate<=\""+enddate+"\" and V2.vacdate>=\""+startdate+"\" and V2.vacdate<=\""+enddate+"\" and V1.code!=V2.code and V1.userID=V2.userID and V1.userID=U.userID) as T";

        try {
            Statement statement = this.connection.createStatement();
            ResultSet rsnum = statement.executeQuery(qnum);
            rsnum.next();
            int num = rsnum.getInt(1);

            QueryResult.UserIDuserNameAddressResult[] arr=new QueryResult.UserIDuserNameAddressResult[num];

            ResultSet rs=statement.executeQuery(q);
            int i=0;
            while(rs.next()){
                arr[i]=new QueryResult.UserIDuserNameAddressResult(""+rs.getInt(1),rs.getString(2),rs.getString(3));
                i++;
            }
            return arr;
        }
        catch (SQLException e){
            e.printStackTrace();
        }

        return new QueryResult.UserIDuserNameAddressResult[0];
    }




    //List side effects experienced by users who have two doses of
    //vaccine with less than 20 days between doses (10 pts)
    //Output: effectcode, effectname
    //Order the results by effectcode in ascending order
    @Override
    public AllergicSideEffect[] getSideEffectsOfUserWhoHaveTwoDosesInLessThanTwentyDays() {
        String q="Select distinct effectcode,effectname from AllergicSideEffect A where exists(select * from Seen S,Vaccination V1,Vaccination V2 where V1.vacdate>V2.vacdate and DATEDIFF(V1.vacdate,V2.vacdate)<20 and V1.code=V2.code and V1.dose!=V2.dose and S.userID=V1.userID and S.code=V1.code and S.effectcode=A.effectcode and V1.userID=V2.userID)order by  effectcode asc;";
        String qnum="Select count(*) from (Select effectcode,effectname from AllergicSideEffect A where exists(select * from Seen S,Vaccination V1,Vaccination V2 where V1.vacdate>V2.vacdate and DATEDIFF(V1.vacdate,V2.vacdate)<20 and V1.code=V2.code and V1.dose!=V2.dose and S.userID=V1.userID and S.code=V1.code and S.effectcode=A.effectcode and V1.userID=V2.userID)group by effectcode,effectname) as T;";

        try {
            Statement statement = this.connection.createStatement();
            ResultSet rsnum = statement.executeQuery(qnum);
            rsnum.next();
            int num = rsnum.getInt(1);

            AllergicSideEffect[] arr=new AllergicSideEffect[num];

            ResultSet rs=statement.executeQuery(q);
            int i=0;
            while(rs.next()){
                arr[i]=new AllergicSideEffect(rs.getInt(1),rs.getString(2));
                i++;
            }
            return arr;
        }
        catch (SQLException e){
            e.printStackTrace();
        }

        return new AllergicSideEffect[0];
    }



    //Calculate the average number of doses of vaccinated users
    //over the age of 65 (5 pts)
    //Output: the average result of applied doses for the given conditio
    @Override
    public double averageNumberofDosesofVaccinatedUserOverSixtyFiveYearsOld() {
        String q="select avg(ccc) from (select count(*) as ccc from User U,Vaccination V where U.age>65 and U.userID=V.userID group by U.userID) as T;";
        try{
            Statement statement = this.connection.createStatement();
            ResultSet rs = statement.executeQuery(q);
            rs.next();
            double num = rs.getDouble(1);
            return num;
        }
        catch (SQLException e){
            e.printStackTrace();
        }

        return 0;
    }

    /*
    User (userID:int, userName:varchar(30), age:int, address:varchar(150), password:varchar(30),
    status:varchar(15))
    Vaccine (code:int, vaccinename:varchar(30), type:varchar(30))
    Vaccination (code:int, userID:int, dose:int, vacdate:date) References Vaccine (code), User(userID)
    AllergicSideEffect (effectcode:int, effectname:varchar(50))
    Seen (effectcode:int, code:int, userID:int, date:date, degree:varchar(30)) References AllergicSideEffect (effectcode), Vaccination (code), User (userID)
    */

    //Update his/her status to “eligible” after 120 days have
    //passed since the user was vaccinated last time (10 pts)
    //Input: given date
    //Output: number of rows affected.
    @Override
    public int updateStatusToEligible(String givendate) {
        String q="Update User U,(select V.userID as USD,max(vacdate) as mydate from Vaccination V group by USD) as T " +
                "set U.status=\"eligible\" " +
                "where DATEDIFF(\""+givendate+"\",T.mydate)>=120 and U.userID=T.USD and U.status!=\"eligible\";";
        try{
            Statement statement = this.connection.createStatement();
            int num = statement.executeUpdate(q);
            return num;
        }
        catch (SQLException e){
            e.printStackTrace();
        }


/*
        Update User U,(select V.userID as USD,max(vacdate) as mydate from Vaccination V group by USD) as T
        set U.status="eligible"
        where DATEDIFF(T.mydate,   givendate    )>=120 and U.userID=T.USD;*/


        return 0;
    }


    /*
    User (userID:int, userName:varchar(30), age:int, address:varchar(150), password:varchar(30),
    status:varchar(15))
    Vaccine (code:int, vaccinename:varchar(30), type:varchar(30))
    Vaccination (code:int, userID:int, dose:int, vacdate:date) References Vaccine (code), User(userID)
    AllergicSideEffect (effectcode:int, effectname:varchar(50))
    Seen (effectcode:int, code:int, userID:int, date:date, degree:varchar(30)) References AllergicSideEffect (effectcode), Vaccination (code), User (userID)
    */

    //Given vaccine name, delete the vaccine(s) from the database
    //(5 pts)
    //Note that related allergic side effects of the vaccine(s) should be deleted as well. You should
    //handle that by design of your schema.
    //Input: vaccinename
    //Output: number of rows in the vaccine table after delete operation.
    @Override
    public Vaccine deleteVaccine(String vaccineName) {
        String q="delete from Vaccine where vaccinename=\""+vaccineName+"\"";
        String q2="Select * from Vaccine where vaccinename=\""+vaccineName+"\"";

        try{
            Statement statement2 = this.connection.createStatement();
            ResultSet rs=statement2.executeQuery(q2);
            
            rs.next();
            Vaccine res=new Vaccine(rs.getInt(1),rs.getString(2),rs.getString(3));

            Statement statement = this.connection.createStatement();
            statement.executeUpdate(q);

            return res;
        }
        catch (SQLException e){
            e.printStackTrace();
        }

 /*
insert into Seen Values(1234,81,1,"1999-09-19","CRAZZZZZZZY");
insert into Vaccination Values(81,1,1,"1999-09-19");
delete from Vaccine where vaccinename="Convidecia";
  */
/*
mysql> select* from Seen;
+------------+------+--------+------------+-------------+
| effectcode | code | userID | date       | degree      |
+------------+------+--------+------------+-------------+
|       1234 |   11 |      5 | 2021-09-10 | Moderate    |
|       1234 |   81 |      1 | 1999-09-19 | CRAZZZZZZZY |
|       1672 |  101 |      7 | 2021-11-25 | Low         |
|       1888 |   11 |      2 | 2021-06-11 | Moderate    |
|       1888 |   21 |     11 | 2021-10-12 | Moderate    |
|       2049 |   41 |     20 | 2021-10-10 | Low         |
|       2101 |  101 |     19 | 2021-12-04 | High        |
|       3501 |  101 |     19 | 2021-12-04 | Moderate    |
|       3502 |   11 |      3 | 2021-12-01 | Low         |
|       3502 |   61 |      9 | 2021-10-25 | High        |
+------------+------+--------+------------+-------------+
10 rows in set (0,00 sec)

mysql> select * from Vaccination;
+------+--------+------+------------+
| code | userID | dose | vacdate    |
+------+--------+------+------------+
|   11 |      1 |    1 | 2021-04-24 |
|   11 |      1 |    2 | 2021-05-29 |
|   11 |      1 |    3 | 2021-12-18 |
|   11 |      2 |    1 | 2021-05-24 |
|   11 |      2 |    2 | 2021-06-10 |
|   11 |      3 |    3 | 2021-12-01 |
|   11 |      5 |    1 | 2021-09-10 |
|   11 |      5 |    2 | 2021-12-11 |
|   11 |      8 |    1 | 2021-01-10 |
|   11 |     10 |    1 | 2021-06-10 |
|   11 |     10 |    2 | 2021-07-07 |
|   11 |     18 |    1 | 2021-09-03 |
|   21 |      6 |    1 | 2021-10-15 |
|   21 |     11 |    1 | 2021-10-10 |
|   41 |     20 |    1 | 2021-10-10 |
|   41 |     20 |    2 | 2021-11-01 |
|   61 |      9 |    1 | 2021-10-20 |
|   61 |     15 |    1 | 2021-09-10 |
|   61 |     17 |    1 | 2021-06-03 |
|   81 |      1 |    1 | 1999-09-19 |
|  101 |      3 |    1 | 2021-06-15 |
|  101 |      3 |    2 | 2021-07-14 |
|  101 |      4 |    1 | 2021-12-01 |
|  101 |      7 |    1 | 2021-11-10 |
|  101 |      7 |    2 | 2021-11-25 |
|  101 |     12 |    1 | 2021-03-01 |
|  101 |     13 |    1 | 2021-01-30 |
|  101 |     14 |    1 | 2021-02-10 |
|  101 |     16 |    1 | 2021-12-18 |
|  101 |     19 |    1 | 2021-07-16 |
|  101 |     19 |    2 | 2021-12-04 |
+------+--------+------+------------+
31 rows in set (0,01 sec)
 */
        return null;
    }
}
