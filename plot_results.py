import pandas as pd
import matplotlib.pyplot as plt
import glob

csv_files = glob.glob('journal_*.csv')

if not csv_files:
    csv_files = glob.glob('casino_journal.csv')

if not csv_files:
    print("CSV файлы не найдены! Запустите симулятор.")
    exit()

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))

for file in csv_files:
    df = pd.read_csv(file)
    
    spins = df.index + 1 
    
    ax1.plot(spins, df['Баланс Игрока'], marker='.', label=file.replace('.csv', ''))
    
    ax2.plot(spins, df['Баланс Кассы'], linestyle='--', label=file.replace('.csv', ''))

ax1.set_title('Стратегия Мартингейл: Баланс игрока', fontsize=14)
ax1.set_xlabel('Номер вращения (Спин)', fontsize=12)
ax1.set_ylabel('Сумма (фишки)', fontsize=12)
ax1.grid(True, linestyle=':', alpha=0.7)
ax1.legend()

ax2.set_title('Изменение баланса кассы казино', fontsize=14)
ax2.set_xlabel('Номер вращения (Спин)', fontsize=12)
ax2.set_ylabel('Сумма (фишки)', fontsize=12)
ax2.grid(True, linestyle=':', alpha=0.7)
ax2.legend()

plt.tight_layout()

plt.savefig('simulation_results.png', dpi=300)
print("Графики успешно построены и сохранены в 'simulation_results.png'.")