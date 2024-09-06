import matplotlib.pyplot as plt
import seaborn as sns

def plot_metrics(queries, precision, recall, f1_scores):
    sns.set(style="whitegrid")

    fig, axes = plt.subplots(1, 3, figsize=(18, 6), sharey=True)

    # Precision Plot
    sns.barplot(x=queries, y=precision, ax=axes[0], palette='Blues_d')
    axes[0].set_title('Precision')
    axes[0].set_xlabel('Queries')
    axes[0].set_ylabel('Score')

    # Recall Plot
    sns.barplot(x=queries, y=recall, ax=axes[1], palette='Greens_d')
    axes[1].set_title('Recall')
    axes[1].set_xlabel('Queries')

    # F1 Score Plot
    sns.barplot(x=queries, y=f1_scores, ax=axes[2], palette='Reds_d')
    axes[2].set_title('F1 Score')
    axes[2].set_xlabel('Queries')

    plt.tight_layout()
    plt.show()
