package com.ubi.class02;

/**
 *
 * @author simoes
 */
public class Class02 {
    
    public static void main(String[] args) {
        FileIN file = new FileIN("https://www.di.ubi.pt/~jpaulo/ensino/IHC/nutrition.txt");
        
        String[] lines = file.readAll();
        file.close();
        
        
        String[] header = lines[0].split("[|]");
        String[] columns;
        String equalString = "=".repeat(130);
        
        System.out.println(equalString);
        System.out.printf("| %-35s | %13s | %13s | %13s | %14s| %13s | %8s |\n", header[0], header[1], header[2], header[3] , header[4], header[5], "kcal/100g");
        System.out.println(equalString);

        double calciumSum = 0;
        double weightSum = 0;
        double waterSum = 0;
        double kcalSum = 0;
        double kcal100gSum = 0;
        
        for(int i = 1; i < lines.length; i++) {
            columns = lines[i].split("[|]");
            
            double calcium = Double.parseDouble(columns[1]);
            double weight = Double.parseDouble(columns[3]);
            double water = Double.parseDouble(columns[4]);
            double kcal = Double.parseDouble(columns[5]);
            double kcal100g = 100 * kcal / weight;
            
            System.out.printf("| %-35s | %13.2f | %13s | %13.2f | %13.2f | %13.2f | %9.2f |\n", columns[0], calcium, columns[2], weight, water, kcal, kcal100g);
            
            calciumSum += calcium;
            weightSum += weight;
            waterSum += water;
            kcalSum += kcal;
            kcal100gSum += kcal100g;
        }       
        
        int size = lines.length - 1;
        
        System.out.println("-".repeat(130));
        System.out.printf("| %-35s | %13.2f | %13s | %13.2f | %13.2f | %13.2f | %9.2f |\n", "Average", calciumSum / size, "-".repeat(13), weightSum / size, waterSum / size, kcalSum / size, kcal100gSum / size);
        System.out.println(equalString);
    }
}
