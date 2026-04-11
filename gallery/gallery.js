const manifestPath = document.body.dataset.manifestPath;
const imageRoot = document.body.dataset.imageRoot;

const elements = {
    totalCount: document.getElementById("total-count"),
    visibleCount: document.getElementById("visible-count"),
    activeLabel: document.getElementById("active-label"),
    searchInput: document.getElementById("search-input"),
    sortSelect: document.getElementById("sort-select"),
    statusText: document.getElementById("status-text"),
    clearSearch: document.getElementById("clear-search"),
    galleryGrid: document.getElementById("gallery-grid"),
    cardTemplate: document.getElementById("card-template"),
    lightbox: document.getElementById("lightbox"),
    toggleDetails: document.getElementById("toggle-details"),
    toggleFullscreen: document.getElementById("toggle-fullscreen"),
    closeLightbox: document.getElementById("close-lightbox"),
    lightboxImage: document.getElementById("lightbox-image"),
    lightboxFamily: document.getElementById("lightbox-family"),
    lightboxTitle: document.getElementById("lightbox-title"),
    lightboxCaption: document.getElementById("lightbox-caption"),
    lightboxTags: document.getElementById("lightbox-tags"),
    lightboxFile: document.getElementById("lightbox-file"),
    lightboxTime: document.getElementById("lightbox-time"),
    downloadLink: document.getElementById("download-link"),
    openFileLink: document.getElementById("open-file-link"),
    prevButton: document.getElementById("prev-button"),
    nextButton: document.getElementById("next-button")
};

const state = {
    items: [],
    filteredItems: [],
    searchTerm: "",
    sortMode: "newest",
    activeFile: null,
    lightboxExpanded: false,
    detailsCollapsed: false
};

function imageUrl(file) {
    return `${imageRoot}/${file}`;
}

function normalizeText(value) {
    return value.toLowerCase().trim();
}

function compareByTimestamp(left, right, direction) {
    const leftTime = left.sortTimestamp ?? -1;
    const rightTime = right.sortTimestamp ?? -1;

    if (leftTime !== rightTime) {
        return direction === "asc" ? leftTime - rightTime : rightTime - leftTime;
    }

    return left.file.localeCompare(right.file);
}

function sortItems(items) {
    const sorted = [...items];

    switch (state.sortMode) {
        case "oldest":
            sorted.sort((left, right) => compareByTimestamp(left, right, "asc"));
            break;
        case "name":
            sorted.sort((left, right) => left.file.localeCompare(right.file));
            break;
        case "rule":
            sorted.sort((left, right) => (left.ruleLabel ?? left.title).localeCompare(right.ruleLabel ?? right.title));
            break;
        case "newest":
        default:
            sorted.sort((left, right) => compareByTimestamp(left, right, "desc"));
            break;
    }

    return sorted;
}

function applyFilters() {
    const query = normalizeText(state.searchTerm);
    const filtered = state.items.filter((item) => {
        if (!query) {
            return true;
        }

        return item.searchText.includes(query);
    });

    state.filteredItems = sortItems(filtered);

    if (state.activeFile && !state.filteredItems.some((item) => item.file === state.activeFile)) {
        closeLightbox();
    }
}

function createTag(label) {
    const tag = document.createElement("span");
    tag.className = "tag";
    tag.textContent = label;
    return tag;
}

function renderCards() {
    elements.galleryGrid.textContent = "";

    if (state.filteredItems.length === 0) {
        const emptyState = document.createElement("section");
        emptyState.className = "empty-state";
        emptyState.innerHTML = "<h2>No screenshots match this filter</h2><p>Try a broader search term or switch the sort order.</p>";
        elements.galleryGrid.append(emptyState);
        return;
    }

    const fragment = document.createDocumentFragment();

    state.filteredItems.forEach((item) => {
        const node = elements.cardTemplate.content.firstElementChild.cloneNode(true);
        const imageButton = node.querySelector(".card-image-button");
        const image = node.querySelector(".card-image");
        const family = node.querySelector(".card-family");
        const title = node.querySelector(".card-title");
        const caption = node.querySelector(".card-caption");
        const tags = node.querySelector(".card-tags");
        const file = node.querySelector(".card-file");

        image.src = imageUrl(item.file);
        image.alt = item.title;
        family.textContent = item.family;
        title.textContent = item.title;
        caption.textContent = item.caption;
        file.textContent = item.file;

        item.tags.forEach((label) => tags.append(createTag(label)));

        imageButton.addEventListener("click", () => openLightbox(item.file));
        fragment.append(node);
    });

    elements.galleryGrid.append(fragment);
}

function updateStatus() {
    elements.totalCount.textContent = String(state.items.length);
    elements.visibleCount.textContent = String(state.filteredItems.length);
    elements.clearSearch.hidden = state.searchTerm.length === 0;

    if (state.filteredItems.length === state.items.length && state.searchTerm.length === 0) {
        elements.statusText.textContent = `${state.items.length} screenshots ready to browse.`;
        return;
    }

    elements.statusText.textContent = `${state.filteredItems.length} of ${state.items.length} screenshots visible.`;
}

function currentIndex() {
    return state.filteredItems.findIndex((item) => item.file === state.activeFile);
}

function syncHash(file) {
    const url = new URL(window.location.href);

    if (!file) {
        url.hash = "";
    } else {
        url.hash = encodeURIComponent(file);
    }

    window.history.replaceState({}, "", url);
}

function syncLightboxChrome() {
    elements.lightbox.classList.toggle("lightbox-expanded", state.lightboxExpanded);
    elements.lightbox.classList.toggle("lightbox-details-collapsed", state.detailsCollapsed);
    elements.toggleFullscreen.setAttribute("aria-pressed", String(state.lightboxExpanded));
    elements.toggleFullscreen.textContent = state.lightboxExpanded ? "Exit Full Screen" : "Full Screen";
    elements.toggleDetails.hidden = !state.lightboxExpanded;
    elements.toggleDetails.setAttribute("aria-expanded", String(!state.detailsCollapsed));
    elements.toggleDetails.textContent = state.detailsCollapsed ? "Show Details" : "Hide Details";
}

function setDetailsCollapsed(collapsed) {
    state.detailsCollapsed = collapsed;
    syncLightboxChrome();
}

function setLightboxExpanded(expanded) {
    state.lightboxExpanded = expanded;

    if (expanded) {
        state.detailsCollapsed = true;
    } else {
        state.detailsCollapsed = false;
    }

    syncLightboxChrome();
}

function closeLightbox() {
    setLightboxExpanded(false);
    state.activeFile = null;
    elements.activeLabel.textContent = "None";
    syncHash(null);

    if (elements.lightbox.open) {
        elements.lightbox.close();
    }
}

function updateLightbox() {
    const index = currentIndex();

    if (index < 0) {
        closeLightbox();
        return;
    }

    const item = state.filteredItems[index];
    const fileUrl = imageUrl(item.file);

    state.activeFile = item.file;
    elements.activeLabel.textContent = item.title;
    elements.lightboxImage.src = fileUrl;
    elements.lightboxImage.alt = item.title;
    elements.lightboxFamily.textContent = item.family;
    elements.lightboxTitle.textContent = item.title;
    elements.lightboxCaption.textContent = item.caption;
    elements.lightboxFile.textContent = item.file;
    elements.lightboxTime.textContent = item.capturedAtDisplay || "Unknown";
    elements.downloadLink.href = fileUrl;
    elements.openFileLink.href = fileUrl;
    elements.lightboxTags.textContent = "";
    item.tags.forEach((label) => elements.lightboxTags.append(createTag(label)));
    elements.prevButton.disabled = index <= 0;
    elements.nextButton.disabled = index >= state.filteredItems.length - 1;
    syncHash(item.file);
}

function openLightbox(file) {
    state.activeFile = file;
    updateLightbox();

    if (!elements.lightbox.open) {
        elements.lightbox.showModal();
    }
}

function stepLightbox(offset) {
    const index = currentIndex();
    const nextIndex = index + offset;

    if (nextIndex < 0 || nextIndex >= state.filteredItems.length) {
        return;
    }

    openLightbox(state.filteredItems[nextIndex].file);
}

function attachEvents() {
    elements.searchInput.addEventListener("input", (event) => {
        state.searchTerm = event.target.value;
        applyFilters();
        renderCards();
        updateStatus();
    });

    elements.sortSelect.addEventListener("change", (event) => {
        state.sortMode = event.target.value;
        applyFilters();
        renderCards();
        updateStatus();
        updateLightbox();
    });

    elements.clearSearch.addEventListener("click", () => {
        elements.searchInput.value = "";
        state.searchTerm = "";
        applyFilters();
        renderCards();
        updateStatus();
    });

    elements.toggleDetails.addEventListener("click", () => {
        if (!state.lightboxExpanded) {
            return;
        }

        setDetailsCollapsed(!state.detailsCollapsed);
    });

    elements.toggleFullscreen.addEventListener("click", () => {
        if (!elements.lightbox.open) {
            return;
        }

        setLightboxExpanded(!state.lightboxExpanded);
    });

    elements.closeLightbox.addEventListener("click", closeLightbox);
    elements.prevButton.addEventListener("click", () => stepLightbox(-1));
    elements.nextButton.addEventListener("click", () => stepLightbox(1));
    elements.lightbox.addEventListener("click", (event) => {
        if (event.target === elements.lightbox) {
            closeLightbox();
        }
    });
    elements.lightbox.addEventListener("cancel", (event) => {
        event.preventDefault();
        closeLightbox();
    });
    elements.lightbox.addEventListener("close", () => {
        if (!elements.lightbox.open) {
            setLightboxExpanded(false);
            state.activeFile = null;
            elements.activeLabel.textContent = "None";
            syncHash(null);
        }
    });

    document.addEventListener("keydown", (event) => {
        if (!elements.lightbox.open) {
            return;
        }

        if (event.key === "Escape") {
            event.preventDefault();
            closeLightbox();
        } else if (event.key === "ArrowLeft") {
            event.preventDefault();
            stepLightbox(-1);
        } else if (event.key === "ArrowRight") {
            event.preventDefault();
            stepLightbox(1);
        } else if ((event.key === "f" || event.key === "F") && !event.altKey && !event.ctrlKey && !event.metaKey) {
            event.preventDefault();
            setLightboxExpanded(!state.lightboxExpanded);
        }
    });
}

function hydrateFromHash() {
    const fileFromHash = decodeURIComponent(window.location.hash.replace(/^#/, ""));

    if (!fileFromHash) {
        return;
    }

    if (state.filteredItems.some((item) => item.file === fileFromHash)) {
        openLightbox(fileFromHash);
    }
}

async function loadGallery() {
    const response = await fetch(manifestPath, { cache: "no-store" });

    if (!response.ok) {
        throw new Error(`Unable to load gallery manifest (${response.status})`);
    }

    const manifest = await response.json();
    state.items = manifest.items.map((item) => ({
        ...item,
        searchText: item.searchText.toLowerCase()
    }));

    applyFilters();
    renderCards();
    updateStatus();
    hydrateFromHash();
}

attachEvents();
syncLightboxChrome();

loadGallery().catch((error) => {
    console.error(error);
    elements.statusText.textContent = "Could not load the screenshot manifest.";
    elements.galleryGrid.innerHTML = "<section class=\"empty-state\"><h2>Gallery unavailable</h2><p>The page loaded, but the screenshot manifest did not. Check the browser console or rebuild the Pages artifact.</p></section>";
});
