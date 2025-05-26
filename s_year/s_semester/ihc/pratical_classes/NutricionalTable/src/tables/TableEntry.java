package tables;

public class TableEntry {
    private String name;
    private int calcium;
    private int weight;
    private int water;
    private int energy;

    public TableEntry(String name, int calcium, int weight, int water, int energy) {
        this.name = name;
        this.calcium = calcium;
        this.weight = weight;
        this.water = water;
        this.energy = energy;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getCalcium() {
        return calcium;
    }

    public void setCalcium(int calcium) {
        this.calcium = calcium;
    }

    public int getWeight() {
        return weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public int getWater() {
        return water;
    }

    public void setWater(int water) {
        this.water = water;
    }

    public int getEnergy() {
        return energy;
    }

    public void setEnergy(int energy) {
        this.energy = energy;
    }
}
