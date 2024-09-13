document.getElementById('calculator-form').addEventListener('submit', async (event) => {
    event.preventDefault();

    const formData = new FormData(event.target);
    const response = await fetch('/calculate', {
        method: 'POST',
        body: new URLSearchParams(formData)
    });

    const result = await response.json();
    document.getElementById('result').textContent = `Monthly Payment: $${result.monthlyPayment}`;
});
