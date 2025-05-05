# 🧪 Batik Wastewater Treatment System with Adaptive MRAC Control

This project is the final undergraduate thesis of **Caleb Effendi**, conducted at the **Institut Teknologi Bandung**, under the Engineering Physics Department. The research focuses on the **optimization of a batik wastewater adsorption system** and the **design of an adaptive MRAC (Model Reference Adaptive Control)** to improve the system’s performance in reducing turbidity.

## 📘 Project Overview

Batik production in Indonesia generates wastewater containing residual dyes, contributing to serious environmental issues. This project implements an adsorption system using a **fixed-bed method** with the following objectives:

- **System identification** using turbidity sensor data.
- **Optimization** of the adsorption system structure using **MINLP (Mixed Integer Non-Linear Programming)**.
- **Design and simulation** of an **adaptive MRAC control model** to improve the turbidity reduction process.

## 🛠️ Features

- **Data Acquisition** using turbidity sensors and **ThingSpeak**.
- **System Identification** via first-order system modeling with time delay.
- **Adaptive Control (MRAC)** implementation using simulation in MATLAB.
- **Optimization of system configuration** for minimal tank/pump usage using MINLP.
- **Achieved turbidity reduction** from 200 NTU to under 100 NTU.

## 📊 System Model Summary

- System modeled as:  
  $$ G(s) = \frac{k}{\tau s + 1} e^{-Ls} $$
- Gain range: 7.06 – 51.96  
- Time constant (τ): 1331 – 3293 seconds  
- Reference model τ (MRAC): 859 seconds  
- Control parameters: θ₀, γ derived from system ID


## 🔧 Requirements

- MATLAB (Recommended R2022a or later)
- Statistics and Optimization Toolbox
- Internet connection for ThingSpeak data retrieval

## 🚀 Getting Started

1. Clone this repository:
   ```bash
   git clone https://github.com/Colazzx/final_Project_ITB.git
   cd final_Project_ITB
