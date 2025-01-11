import pandas as pd
import matplotlib.pyplot as plt

import matplotlib as lib
import seaborn as sea
import numpy as np

sea.set_theme(style="whitegrid")
sea.set(font_scale=0.75)
data = pd.read_csv(r"D:\Comp101\COMP170-2309236/assets\by-ethnicity-over-time.csv")
data = data[data["Time"] != "2022"]
# Ignores any data from the year 2022
data = data[data["Time"] != "2021"]
# Ignores any data from the year 2021
sea.color_palette("icefire", as_cmap=True)  # Initalises palette "icefire"
sea.set(rc={"figure.figsize": (8, 4)})
sea.catplot(
    data=data, kind="bar",
    # Plots a grouped bar chart with "Time" as the groups, "Ethnicity" as the x-axis and "% Exercise as the y
    x="Ethnicity", y="% Exercise", hue="Time",
    errorbar="sd", palette="icefire", alpha=.6, height=6,
).set(title="% Exercise per Ethnicity")

sea.set_theme(style="whitegrid")
sea.set(font_scale=0.75)
data = pd.read_csv(r"D:\Comp101\COMP170-2309236/assets\by-ethnicity-over-time-Obesity(1).csv")
data = data[data["Ethnicity"] != "Unknown"]  # This ignores all the data in the "Unknown" ethnicity
data = data[data["Time"] != "2015"]  # Ignores any data from the year 2015
sea.color_palette("icefire", as_cmap=True)  # Initalises palette "icefire"
sea.set(rc={"figure.figsize": (8, 3)})
sea.catplot(
    data=data, kind="bar",
    # Plots a grouped bar chart with "Time" as the groups, "Ethnicity" as the x-axis and "% Obesity as the y
    x="Ethnicity", y="% Obesity", hue="Time",
    errorbar="sd", palette="icefire", alpha=.6, height=6,
).set(title="% Obesity per Ethnicity")

sea.set_theme(style="whitegrid")
sea.set(font_scale=0.85)
sea.color_palette("coolwarm", as_cmap=True)  # Initalises palette "icefire"
data = pd.read_csv(r"D:\Comp101\COMP170-2309236/assets\by-ethnicity-over-time-Obesity(1).csv")
plt.figure(figsize=(8, 15))
data = data[data["Time"] != "2015"]  # Ignores any data from the year 2015
data = data[data["Time"] != "Overall Change 2016-2020"]  # Ignores the data on the overall % change
data = data[data["Ethnicity"] != "Unknown"]  # This ignores all the data in the "Unknown" ethnicity
sea.boxplot(data=data, x="% Obesity", y="Ethnicity", palette="coolwarm")
plt.title("% Obesity per Ethnicity")
plt.show()

sea.set_theme(style="whitegrid")
sea.set(font_scale=0.75)
sea.color_palette("coolwarm", as_cmap=True)
data = pd.read_csv(r"D:\Comp101\COMP170-2309236/assets\by-ethnicity-over-time.csv")
data = data[data["Time"] != "Overall Change 2016-2020"]  # Ignores the data on the overall % change
data = data[data["Time"] != "2022"]  # Ignores any data from the year 2022
data = data[data["Time"] != "2021"]  # Ignores any data from the year 2021
plt.figure(figsize=(8, 15))
sea.boxplot(data=data, x="% Exercise", y="Ethnicity", palette="coolwarm")
plt.title("% Exercise per Ethnicity")
plt.show()

sea.set_theme(style="whitegrid")
sea.set(font_scale=0.85)
data_obesity = pd.read_csv(
    r"D:\Comp101\COMP170-2309236/assets\by-ethnicity-over-time-Obesity(1).csv")
# This will read the csv and store it as data_obesity
data_exercise = pd.read_csv(
    r"D:\Comp101\COMP170-2309236/assets\by-ethnicity-over-time.csv")
# This will read the csv and store it as data_exercise
data_obesity = data_obesity[data_obesity["Time"] != "2015"]  # Ignores any data from the year 2015
data_obesity = data_obesity[
    data_obesity["Time"] != "Overall Change 2016-2020"]  # Ignores the data on the overall % change
data_exercise = data_exercise[data_exercise["Time"] != "2022"]  # Ignores any data from the year 2022
data_exercise = data_exercise[data_exercise["Time"] != "2021"]  # Ignores any data from the year 2021
data_exercise = data_exercise[
    data_exercise["Time"] != "Overall Change 2016-2020"]  # Ignores the data on the overall % change
data_mixed = pd.concat([data_obesity, data_exercise],
                       axis=0)  # Combines the two datasets into one, this allows them to be plotted and modified as one
data_mixed = data_mixed[
    data_mixed["Ethnicity"] == "All"]  # Ignores all data for every Ethnicity other than the values for the all category

plt.plot(data_mixed["Time"], data_mixed["% Obesity"], label="% Obesity")  # Plots line graph for "% Obesity"
plt.plot(data_mixed["Time"], data_mixed["% Exercise"], label="% Exercise")  # Plots line graph for "% Exercise"
plt.xlabel('Time')  # Labels X-axis
plt.ylabel('% Value')  # Labels Y-axis
plt.title("% values from 2016 to 2020 of Exercise and Obesity Across The UK")  # Labels Title
plt.legend()  # Adds Legend
plt.show()

sea.set_theme(style="whitegrid")
sea.set(font_scale=0.85)
data_obesity = pd.read_csv(r"D:\Comp101\COMP170-2309236/assets\by-ethnicity-over-time-Obesity(1).csv")
data_exercise = pd.read_csv(r"D:\Comp101\COMP170-2309236/assets\by-ethnicity-over-time.csv")
data_obesity = data_obesity[data_obesity["Ethnicity"] != "Unknown"]
data_obesity = data_obesity[data_obesity["Time"] != "2015"]
data_obesity = data_obesity[data_obesity["Time"] != "Overall Change 2016-2020"]
data_obesity = data_obesity[data_obesity["Ethnicity"] != "All"]
data_exercise = data_exercise[data_exercise["Time"] != "2022"]
data_exercise = data_exercise[data_exercise["Time"] != "2021"]
data_exercise = data_exercise[data_exercise["Time"] != "Overall Change 2016-2020"]
data_exercise = data_exercise[data_exercise["Ethnicity"] != "All"]

data_mixed = pd.concat([data_obesity, data_exercise], axis=1)
data_mixed.set_index("Time", inplace=True)

data_mixed.plot(kind="bar", figsize=(10, 5), grid=True)
plt.title("Obesity vs. Exercise")
plt.xlabel("Year")
plt.ylabel("Percentage")
plt.legend(title="Category")
plt.show()
