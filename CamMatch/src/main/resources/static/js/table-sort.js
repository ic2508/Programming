document.addEventListener('DOMContentLoaded', function () {
    document.querySelectorAll('table[data-sortable="true"]').forEach(function (table) {
        const headers = table.querySelectorAll('thead th[data-sort]');
        headers.forEach(function (header, index) {
            header.setAttribute('tabindex', '0');
            header.setAttribute('role', 'button');
            header.title = 'Click pentru sortare';
            const sort = function () {
                const type = header.dataset.sort || 'text';
                const asc = header.dataset.direction !== 'asc';
                headers.forEach(h => h.removeAttribute('data-direction'));
                header.dataset.direction = asc ? 'asc' : 'desc';
                const rows = Array.from(table.querySelectorAll('tbody tr'));
                rows.sort(function (a, b) {
                    const aValue = getValue(a.children[index], type);
                    const bValue = getValue(b.children[index], type);
                    let result;
                    if (type === 'number') {
                        result = aValue - bValue;
                    } else {
                        result = String(aValue).localeCompare(String(bValue), 'ro', {numeric: true, sensitivity: 'base'});
                    }
                    return asc ? result : -result;
                });
                const body = table.querySelector('tbody');
                rows.forEach(row => body.appendChild(row));
            };
            header.addEventListener('click', sort);
            header.addEventListener('keydown', function (event) {
                if (event.key === 'Enter' || event.key === ' ') {
                    event.preventDefault();
                    sort();
                }
            });
        });
    });
});

function getValue(cell, type) {
    if (!cell) {
        return type === 'number' ? 0 : '';
    }
    const raw = (cell.dataset.sortValue || cell.textContent || '').trim();
    if (type === 'number') {
        const parsed = Number(raw.replace(/[^0-9,.-]/g, '').replace(',', '.'));
        return Number.isFinite(parsed) ? parsed : 0;
    }
    return raw;
}
