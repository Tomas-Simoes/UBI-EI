package com.ubi.class02;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


/**
 * <p>Title: </p>
 *
 * <p>Description: </p>
 *
 * <p>Copyright: Copyright (c) 2007</p>
 *
 * <p>Company: UBI/HULTIG</p>
 *
 * @author JPC
 * @version 1.0
 */
public class FileIN extends File
{
    protected BufferedReader br;
    protected String encode;
    protected URL url;


    /**
     * Constructor. Sets the encoding for the default, which is
     * ISO-8858-1
     * @param fname String
     */
    public FileIN(String fname) {
        super(fname);
        setEncoding("UTF-8");
        //setEncoding("ISO-8859-1");
        try {
            url= new URL(fname);
        } catch (MalformedURLException ex) {
            url= null;
        }
    }

    /**
     * Gives the current encoding.
     * @return String
     */
    public String getEncoding() {
        return this.encode;
    }

    /**
     * Sets the encoding.
     * @param encode String
     */
    public void setEncoding(String encode) {
        if ( encode == null || encode.length() < 1 )  return;

        this.encode= encode;
    }

    /**
     * Open/reopen this file.
     */
    public boolean open() {
        try {
            if (url == null) {
                InputStream in = new FileInputStream(this);
                br = new BufferedReader(new InputStreamReader(in, encode));
                return true;
            } else {
                br = new BufferedReader(new InputStreamReader(url.openStream(), encode));
                return true;
            }
        }
        catch (Exception exc) {
            exc.printStackTrace();
            br= null;
            return false;
        }
    }

    /**
     * Close the current file.
     */
    public void close() {
        try {
            br.close();
        }
        catch (Exception exc) {}
    }


    public static boolean existsURLresource(String URLName) {
        try {
            HttpURLConnection.setFollowRedirects(false);
            // note : you may also need
            //        HttpURLConnection.setInstanceFollowRedirects(false)
            HttpURLConnection con =
                    (HttpURLConnection) new URL(URLName).openConnection();
            con.setRequestMethod("HEAD");
            return (con.getResponseCode() == HttpURLConnection.HTTP_OK);
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }


    /**
     * Count the number of lines in this file. 
     * @return The number of lines counted. The
     * file will end closed!.
     */
    public int countNumLines() {
        int counter= 0;
        open();
        while ( this.read() != null ) counter++;
        close();
        return counter;
    }


    /**
     * Reads all strings from file.
     * @return String[]
     */
    public String[] readAll() {
        open();
        if ( br == null ) return null;

        ArrayList<String> v= new  ArrayList<String>();
        try {
            for (; ; ) {
                String line = br.readLine();
                if (line == null) break;

                v.add(line);
            }
            br.close();
        }
        catch (Exception exc) {
            exc.printStackTrace();
        }

        String[] vs= v.toArray(new String[v.size()]);
        return vs;
    }


    /**
     * Reads the next line from the opened text.
     * @return The line read or else the null value.
     */
    public String read() {
        try {
            return br.readLine();
        }
        catch(Exception exc) {
            return null;
        }
    }


    /**
     * Reads a maximum amount of strings, from this file.
     * @param limit int
     * @return String[]
     */
    public String[] read(int limit) {
        open();
        if ( br == null ) {
            return null;
        }

        ArrayList<String> v= new  ArrayList<String>();
        try {
            for (int i=0; i<limit; i++) {
                String line = br.readLine();
                if (line == null) {
                    break;
                }

                v.add(line);
            }
            br.close();
        }
        catch (Exception exc) {
            exc.printStackTrace();
        }

        String[] vs= v.toArray(new String[v.size()]);
        return vs;
    }


    /**
     * Reads all strings that matches a given regular expression.
     * @param pattern String
     * @return String[]
     */
    public String[] readPattern(String pattern) {
        open();
        if ( br == null ) {
            return null;
        }

        ArrayList<String> v= new  ArrayList<String>();
        try {
            Pattern p= Pattern.compile(pattern);
            for (;;) {
                String line = br.readLine();
                if (line == null) break;

                Matcher m= p.matcher(line);
                if ( m.find() ) {
                    if ( m.groupCount() > 0 ) {
                        StringBuilder sb= new StringBuilder();
                        for (int i = 1; i <= m.groupCount(); i++) {
                            sb.append(m.group(i));
                        }
                        v.add(sb.toString());
                    }
                    else {
                        v.add(line);
                    }
                }
            }
            br.close();
        }
        catch (Exception exc) {
            exc.printStackTrace();
        }

        String[] vs= v.toArray(new String[v.size()]);
        return vs;
    }

    /**
     * Output a static array of strings.
     * @param v String[]
     */
    public static void print(String[] v) {
        for (int i=0; i<v.length; i++) {
            System.out.printf(" v(%02d) ---> [%s]\n", i, v[i]);
        }
    }
}