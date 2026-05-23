package com.cammatch.config;

import com.cammatch.entity.Camera;
import com.cammatch.entity.CameraRating;
import com.cammatch.entity.ForumComment;
import com.cammatch.entity.ForumPost;
import com.cammatch.entity.Role;
import com.cammatch.entity.UserAccount;
import com.cammatch.entity.UserFavorite;
import com.cammatch.repository.CameraRatingRepository;
import com.cammatch.repository.CameraRepository;
import com.cammatch.repository.FavoriteRepository;
import com.cammatch.repository.ForumCommentRepository;
import com.cammatch.repository.ForumPostRepository;
import com.cammatch.repository.SearchHistoryRepository;
import com.cammatch.repository.UserCameraRepository;
import com.cammatch.repository.UserRepository;
import org.springframework.boot.CommandLineRunner;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Component;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.util.List;

@Component
public class DataInitializer implements CommandLineRunner {
    private static final String CURRENT_ADMIN_EMAIL = "admin@cammatch.demo";

    private final UserRepository userRepository;
    private final CameraRepository cameraRepository;
    private final FavoriteRepository favoriteRepository;
    private final ForumPostRepository forumPostRepository;
    private final ForumCommentRepository forumCommentRepository;
    private final CameraRatingRepository cameraRatingRepository;
    private final SearchHistoryRepository searchHistoryRepository;
    private final UserCameraRepository userCameraRepository;
    private final PasswordEncoder passwordEncoder;

    public DataInitializer(UserRepository userRepository,
                           CameraRepository cameraRepository,
                           FavoriteRepository favoriteRepository,
                           ForumPostRepository forumPostRepository,
                           ForumCommentRepository forumCommentRepository,
                           CameraRatingRepository cameraRatingRepository,
                           SearchHistoryRepository searchHistoryRepository,
                           UserCameraRepository userCameraRepository,
                           PasswordEncoder passwordEncoder) {
        this.userRepository = userRepository;
        this.cameraRepository = cameraRepository;
        this.favoriteRepository = favoriteRepository;
        this.forumPostRepository = forumPostRepository;
        this.forumCommentRepository = forumCommentRepository;
        this.cameraRatingRepository = cameraRatingRepository;
        this.searchHistoryRepository = searchHistoryRepository;
        this.userCameraRepository = userCameraRepository;
        this.passwordEncoder = passwordEncoder;
    }

    @Override
    @Transactional
    public void run(String... args) {
        resetUsersOnceForCurrentDemoVersion();
        DemoUsers users = seedUsers();
        seedCameras();
        seedDemoRatings(users);
        seedDemoActivity(users);
    }

    private void resetUsersOnceForCurrentDemoVersion() {
        if (userRepository.existsByEmail(CURRENT_ADMIN_EMAIL)) {
            return;
        }
        forumCommentRepository.deleteAllInBatch();
        forumPostRepository.deleteAllInBatch();
        favoriteRepository.deleteAllInBatch();
        cameraRatingRepository.deleteAllInBatch();
        searchHistoryRepository.deleteAllInBatch();
        userCameraRepository.deleteAllInBatch();
        deleteUserAddedPublicCameras();
        userRepository.deleteAllInBatch();
    }

    private void deleteUserAddedPublicCameras() {
        List<Camera> userAdded = cameraRepository.findAll().stream()
                .filter(camera -> camera.getDescription() != null && camera.getDescription().startsWith("Camera adaugata de utilizatorul"))
                .toList();
        if (!userAdded.isEmpty()) {
            cameraRepository.deleteAllInBatch(userAdded);
        }
    }

    private DemoUsers seedUsers() {
        UserAccount admin = upsertUser("admin", CURRENT_ADMIN_EMAIL, "Admin2026!", Role.ADMIN, "Constanta", "avansat", "Administratorul platformei CamMatch.");
        UserAccount ana = upsertUser("ana.popescu", "ana.popescu@cammatch.demo", "Ana2026!", Role.USER, "Bucuresti", "incepator", "Cauta o camera usoara pentru portrete si calatorii.");
        UserAccount mihai = upsertUser("mihai.ionescu", "mihai.ionescu@cammatch.demo", "Mihai2026!", Role.USER, "Cluj-Napoca", "mediu", "Interesat de camere pentru evenimente si fotografie de familie.");
        UserAccount maria = upsertUser("maria.stan", "maria.stan@cammatch.demo", "Maria2026!", Role.USER, "Iasi", "mediu", "Testeaza camere pentru vlogging si continut video.");
        UserAccount andrei = upsertUser("andrei.dumitru", "andrei.dumitru@cammatch.demo", "Andrei2026!", Role.USER, "Brasov", "avansat", "Pasionat de wildlife, sport si fotografie outdoor.");
        UserAccount vlad = upsertUser("vlad.marin", "vlad.marin@cammatch.demo", "Vlad2026!", Role.USER, "Timisoara", "incepator", "Compara modele compacte pentru calatorii.");
        return new DemoUsers(admin, ana, mihai, maria, andrei, vlad);
    }

    private UserAccount upsertUser(String username, String email, String password, Role role, String city, String experienceLevel, String bio) {
        UserAccount value = userRepository.findByEmail(email).orElseGet(UserAccount::new);
        value.setUsername(username);
        value.setEmail(email);
        value.setPassword(passwordEncoder.encode(password));
        value.setRole(role);
        value.setConfirmed(true);
        value.setActive(true);
        value.setCity(city);
        value.setExperienceLevel(experienceLevel);
        value.setBio(bio);
        return userRepository.save(value);
    }

    private void seedCameras() {
        upsertCamera("Canon", "EOS R50", "Mirrorless", "portret", "APS-C", "4K", "3799.00", 24.2, 370, "Camera usoara pentru incepatori si creatori de continut.");
        upsertCamera("Canon", "EOS R10", "Mirrorless", "sport", "APS-C", "4K", "4999.00", 24.2, 430, "Autofocus rapid si rafala buna pentru actiune.");
        upsertCamera("Canon", "EOS R8", "Mirrorless", "portret", "Full Frame", "4K", "7999.00", 24.2, 370, "Full frame compact, potrivit pentru portrete si evenimente.");
        upsertCamera("Canon", "EOS R6 Mark II", "Mirrorless", "eveniment", "Full Frame", "4K", "12999.00", 24.2, 580, "Model avansat pentru nunti, evenimente si fotografie profesionala.");
        upsertCamera("Canon", "EOS 250D", "DSLR", "incepator", "APS-C", "4K", "2999.00", 24.1, 1070, "DSLR accesibil cu autonomie foarte buna.");
        upsertCamera("Canon", "PowerShot G7 X III", "Compact", "vlogging", "1 inch", "4K", "3699.00", 20.1, 235, "Camera compacta pentru vlogging si continut online.");
        upsertCamera("Nikon", "Z30", "Mirrorless", "vlogging", "APS-C", "4K", "3499.00", 20.9, 330, "Camera compacta pentru video, vlog si social media.");
        upsertCamera("Nikon", "Z50", "Mirrorless", "street", "APS-C", "4K", "4299.00", 20.9, 320, "Model compact pentru fotografie urbana si calatorii.");
        upsertCamera("Nikon", "Z fc", "Mirrorless", "street", "APS-C", "4K", "4999.00", 20.9, 300, "Design retro si controale manuale pentru fotografie creativa.");
        upsertCamera("Nikon", "Z5", "Mirrorless", "portret", "Full Frame", "4K", "6799.00", 24.3, 470, "Full frame accesibil pentru portrete si peisaje.");
        upsertCamera("Nikon", "Z6 II", "Mirrorless", "eveniment", "Full Frame", "4K", "8999.00", 24.5, 410, "Camera full frame echilibrata pentru evenimente si fotografie generala.");
        upsertCamera("Nikon", "D7500", "DSLR", "wildlife", "APS-C", "4K", "5499.00", 20.9, 950, "DSLR robust cu autonomie ridicata pentru natura si sport.");
        upsertCamera("Sony", "A6100", "Mirrorless", "incepator", "APS-C", "4K", "3699.00", 24.2, 420, "Mirrorless accesibil cu autofocus foarte bun.");
        upsertCamera("Sony", "A6400", "Mirrorless", "sport", "APS-C", "4K", "4999.00", 24.2, 410, "Autofocus rapid si performanta buna pentru actiune.");
        upsertCamera("Sony", "ZV-E10", "Mirrorless", "vlogging", "APS-C", "4K", "3899.00", 24.2, 440, "Camera pentru creatori video cu obiective interschimbabile.");
        upsertCamera("Sony", "A7 III", "Mirrorless", "eveniment", "Full Frame", "4K", "8499.00", 24.2, 710, "Full frame popular pentru foto si video.");
        upsertCamera("Sony", "A7 IV", "Mirrorless", "profesional", "Full Frame", "4K", "11999.00", 33.0, 580, "Model performant pentru fotografi avansati si profesionisti.");
        upsertCamera("Sony", "RX100 VII", "Compact", "calatorie", "1 inch", "4K", "5999.00", 20.1, 260, "Compact premium cu zoom versatil pentru calatorii.");
        upsertCamera("Fujifilm", "X-T30 II", "Mirrorless", "street", "APS-C", "4K", "4699.00", 26.1, 380, "Camera mica, rapida si potrivita pentru fotografie urbana.");
        upsertCamera("Fujifilm", "X-S20", "Mirrorless", "video", "APS-C", "6.2K", "6999.00", 26.1, 750, "Autonomie foarte buna si functii video avansate.");
        upsertCamera("Fujifilm", "X-T5", "Mirrorless", "peisaj", "APS-C", "6.2K", "8999.00", 40.2, 580, "Rezolutie mare si controale clasice pentru fotografie avansata.");
        upsertCamera("Fujifilm", "X-H2", "Mirrorless", "profesional", "APS-C", "8K", "9999.00", 40.2, 680, "Camera orientata spre rezolutie mare si video performant.");
        upsertCamera("Fujifilm", "X100V", "Compact", "street", "APS-C", "4K", "7499.00", 26.1, 420, "Compact premium cu obiectiv fix, ideal pentru street photography.");
        upsertCamera("Fujifilm", "GFX 50S II", "Mirrorless", "profesional", "Medium Format", "Full HD", "16999.00", 51.4, 455, "Format mediu pentru calitate maxima a imaginii.");
        upsertCamera("Panasonic", "Lumix G100", "Mirrorless", "vlogging", "Micro Four Thirds", "4K", "2999.00", 20.3, 270, "Model usor pentru vlog si fotografie casual.");
        upsertCamera("Panasonic", "Lumix GH6", "Mirrorless", "video", "Micro Four Thirds", "5.7K", "7499.00", 25.2, 360, "Camera orientata spre filmare si continut video.");
        upsertCamera("Panasonic", "Lumix S5 II", "Mirrorless", "video", "Full Frame", "6K", "8999.00", 24.2, 370, "Full frame hibrid cu stabilizare si autofocus imbunatatit.");
        upsertCamera("Panasonic", "Lumix S5 IIX", "Mirrorless", "profesional", "Full Frame", "6K", "10999.00", 24.2, 370, "Model video avansat pentru creatori si productie.");
        upsertCamera("Olympus", "OM-D E-M10 IV", "Mirrorless", "calatorie", "Micro Four Thirds", "4K", "3299.00", 20.3, 360, "Camera compacta si stabilizata pentru calatorii.");
        upsertCamera("Olympus", "OM-D E-M5 III", "Mirrorless", "calatorie", "Micro Four Thirds", "4K", "5499.00", 20.4, 310, "Corp rezistent si stabilizare buna pentru utilizare zilnica.");
        upsertCamera("OM System", "OM-5", "Mirrorless", "wildlife", "Micro Four Thirds", "4K", "5999.00", 20.4, 310, "Camera rezistenta la intemperii pentru natura si drumetii.");
        upsertCamera("OM System", "OM-1 Mark II", "Mirrorless", "wildlife", "Micro Four Thirds", "4K", "11999.00", 20.4, 520, "Model rapid pentru wildlife, sport si fotografie outdoor.");
        upsertCamera("Leica", "Q2", "Compact", "street", "Full Frame", "4K", "24999.00", 47.3, 350, "Compact full frame premium cu obiectiv fix luminos.");
        upsertCamera("Pentax", "K-70", "DSLR", "peisaj", "APS-C", "Full HD", "3999.00", 24.2, 410, "DSLR rezistent la vreme pentru fotografie outdoor.");
        upsertCamera("Ricoh", "GR III", "Compact", "street", "APS-C", "Full HD", "5299.00", 24.2, 200, "Compact discret si rapid pentru fotografie stradala.");
        upsertCamera("GoPro", "HERO12 Black", "Action", "sport", "1/1.9 inch", "5.3K", "2499.00", 27.0, 180, "Camera action pentru sport, calatorii si filmari dinamice.");
        upsertCamera("DJI", "Osmo Pocket 3", "Compact", "vlogging", "1 inch", "4K", "3199.00", 9.4, 166, "Camera compacta stabilizata pentru vlog si filmari rapide.");
    }


    private void seedDemoRatings(DemoUsers users) {
        List<UserAccount> reviewers = List.of(users.ana(), users.mihai(), users.maria(), users.andrei(), users.vlad());
        cameraRatingRepository.deleteByUserIn(reviewers);

        List<Camera> cameras = cameraRepository.findAllByOrderByBrandAscModelAsc();
        int[][] ratingPatterns = {
                {5, 4, 5, 4, 5},
                {4, 4, 5, 3, 4},
                {3, 4, 3, 4, 2},
                {2, 3, 2, 3, 1},
                {5, 5, 4, 5, 4},
                {1, 2, 2, 1, 3},
                {4, 3, 5, 4, 4},
                {3, 3, 4, 2, 3},
                {5, 4, 4, 3, 5},
                {2, 2, 3, 2, 1}
        };

        for (int index = 0; index < cameras.size(); index++) {
            Camera camera = cameras.get(index);
            int ratingsToAdd = ratingsCountForCamera(index);
            int[] pattern = ratingPatterns[index % ratingPatterns.length];

            for (int reviewerIndex = 0; reviewerIndex < ratingsToAdd; reviewerIndex++) {
                addRating(camera, reviewers.get(reviewerIndex), pattern[reviewerIndex]);
            }
            updateCameraAverage(camera);
        }
    }

    private int ratingsCountForCamera(int index) {
        return switch (index % 8) {
            case 0 -> 0;  // cateva camere raman intentionat Not rated
            case 1 -> 1;
            case 2 -> 2;
            case 3 -> 3;
            case 4 -> 4;
            default -> 5;
        };
    }

    private void addRating(Camera camera, UserAccount user, int stars) {
        CameraRating rating = new CameraRating();
        rating.setCamera(camera);
        rating.setUser(user);
        rating.setStars(Math.max(1, Math.min(5, stars)));
        cameraRatingRepository.save(rating);
    }

    private void updateCameraAverage(Camera camera) {
        List<CameraRating> ratings = cameraRatingRepository.findByCamera(camera);
        if (ratings.isEmpty()) {
            camera.setAverageRating(0.0);
            camera.setRatingCount(0);
        } else {
            double average = ratings.stream().mapToInt(CameraRating::getStars).average().orElse(0.0);
            camera.setAverageRating(Math.round(average * 100.0) / 100.0);
            camera.setRatingCount(ratings.size());
        }
        cameraRepository.save(camera);
    }


    private void seedDemoActivity(DemoUsers users) {
        List<UserAccount> normalUsers = List.of(users.ana(), users.mihai(), users.maria(), users.andrei(), users.vlad());
        List<Camera> cameras = cameraRepository.findAllByOrderByBrandAscModelAsc();
        if (cameras.size() < 10) {
            return;
        }

        resetDemoFavoritesAndForum(normalUsers);

        seedDemoFavorites(users, cameras);
        seedDemoForumPostsAndComments(users);
    }

    private void resetDemoFavoritesAndForum(List<UserAccount> demoUsers) {
        forumCommentRepository.deleteByAuthorIn(demoUsers);

        List<ForumPost> postsByDemoUsers = forumPostRepository.findByAuthorIn(demoUsers);
        if (!postsByDemoUsers.isEmpty()) {
            forumPostRepository.deleteAll(postsByDemoUsers);
        }

        favoriteRepository.deleteByUserIn(demoUsers);
    }

    private void seedDemoFavorites(DemoUsers users, List<Camera> cameras) {
        addFavorite(users.ana(), cameraAt(cameras, 0));
        addFavorite(users.ana(), cameraAt(cameras, 14));
        addFavorite(users.ana(), cameraAt(cameras, 18));
        addFavorite(users.ana(), cameraAt(cameras, 28));

        addFavorite(users.mihai(), cameraAt(cameras, 2));
        addFavorite(users.mihai(), cameraAt(cameras, 3));
        addFavorite(users.mihai(), cameraAt(cameras, 10));
        addFavorite(users.mihai(), cameraAt(cameras, 15));

        addFavorite(users.maria(), cameraAt(cameras, 5));
        addFavorite(users.maria(), cameraAt(cameras, 14));
        addFavorite(users.maria(), cameraAt(cameras, 19));
        addFavorite(users.maria(), cameraAt(cameras, 36));

        addFavorite(users.andrei(), cameraAt(cameras, 11));
        addFavorite(users.andrei(), cameraAt(cameras, 30));
        addFavorite(users.andrei(), cameraAt(cameras, 31));
        addFavorite(users.andrei(), cameraAt(cameras, 35));

        addFavorite(users.vlad(), cameraAt(cameras, 1));
        addFavorite(users.vlad(), cameraAt(cameras, 17));
        addFavorite(users.vlad(), cameraAt(cameras, 23));
        addFavorite(users.vlad(), cameraAt(cameras, 34));
    }

    private Camera cameraAt(List<Camera> cameras, int index) {
        return cameras.get(Math.floorMod(index, cameras.size()));
    }

    private void seedDemoForumPostsAndComments(DemoUsers users) {
        Camera canonR50 = findCamera("Canon", "EOS R50");
        Camera sonyZve10 = findCamera("Sony", "ZV-E10");
        Camera nikonZ50 = findCamera("Nikon", "Z50");
        Camera fujiXs20 = findCamera("Fujifilm", "X-S20");
        Camera olympusOm5 = findCamera("OM System", "OM-5");

        ForumPost post1 = addForumPost(canonR50, users.ana(),
                "Merita Canon EOS R50 pentru inceput?",
                "Vreau o camera pentru portrete si fotografii de vacanta. Ma intereseaza daca este usor de folosit si daca obiectivele sunt accesibile.",
                7);
        addForumComment(post1, users.mihai(), "Da, este foarte buna pentru inceput. Meniurile sunt clare si autofocusul ajuta mult la portrete.", 6);
        addForumComment(post1, users.vlad(), "Am pus-o la favorite pentru ca este usoara si pretul este bun pentru un prim aparat.", 5);
        addForumComment(post1, users.maria(), "Pentru video casual este ok, dar daca vrei vlogging zilnic m-as uita si la Sony ZV-E10.", 4);

        ForumPost post2 = addForumPost(sonyZve10, users.maria(),
                "Sony ZV-E10 pentru vlog si YouTube",
                "Caut un model cu obiective interschimbabile, autofocus bun si calitate video peste telefon. Are sens ZV-E10 in buget mediu?",
                6);
        addForumComment(post2, users.ana(), "Pentru continut video este foarte potrivita. Imi place ca are ecran rabatabil si imagine buna.", 5);
        addForumComment(post2, users.andrei(), "Pentru sport nu este prima alegere, dar pentru vlog si review-uri este o varianta reusita.", 4);
        addForumComment(post2, users.vlad(), "Am salvat-o la favorite pentru calatorii, mai ales daca folosesti un obiectiv compact.", 3);

        ForumPost post3 = addForumPost(nikonZ50, users.vlad(),
                "Nikon Z50 pentru calatorii",
                "Mi se pare un model echilibrat pentru vacante si fotografie stradala. Cum vi se pare autonomia?",
                5);
        addForumComment(post3, users.ana(), "Pentru o zi de plimbare este ok, dar as lua o baterie de rezerva.", 4);
        addForumComment(post3, users.mihai(), "Ergonomia este mai buna decat la multe modele compacte. Pentru familie si calatorii mi se pare inspirata.", 3);

        ForumPost post4 = addForumPost(fujiXs20, users.mihai(),
                "Fujifilm X-S20 pentru foto si video",
                "Ma intereseaza o camera care sa fie buna si pentru poze, si pentru filmari. X-S20 pare foarte echilibrata.",
                4);
        addForumComment(post4, users.maria(), "Pentru video este una dintre cele mai bune variante APS-C din lista. Autonomia este un avantaj mare.", 3);
        addForumComment(post4, users.andrei(), "Pentru outdoor as verifica si rezistenta la vreme, dar specificatiile sunt foarte bune.", 2);
        addForumComment(post4, users.ana(), "Culorile Fujifilm sunt un plus daca nu vrei sa editezi foarte mult pozele.", 1);

        ForumPost post5 = addForumPost(olympusOm5, users.andrei(),
                "OM-5 pentru wildlife si drumetii",
                "Caut ceva rezistent la vreme, usor de carat si potrivit pentru natura. OM-5 pare interesanta pentru excursii.",
                3);
        addForumComment(post5, users.vlad(), "Pentru drumetii conteaza mult greutatea, iar sistemul Micro Four Thirds are obiective mici.", 2);
        addForumComment(post5, users.mihai(), "As alege-o pentru outdoor, mai ales daca vrei stabilizare buna si kit compact.", 1);
        addForumComment(post5, users.maria(), "Nu este orientata strict spre video, dar pentru calatorii si natura este foarte practica.", 0);
    }

    private Camera findCamera(String brand, String model) {
        return cameraRepository.findByBrandIgnoreCaseAndModelIgnoreCase(brand, model)
                .orElseThrow(() -> new IllegalStateException("Camera demo lipsa: " + brand + " " + model));
    }

    private ForumPost addForumPost(Camera camera, UserAccount author, String title, String content, int daysAgo) {
        ForumPost post = new ForumPost();
        post.setCamera(camera);
        post.setAuthor(author);
        post.setTitle(title);
        post.setContent(content);
        post.setApproved(true);
        post.setCreatedAt(LocalDateTime.now().minusDays(daysAgo));
        return forumPostRepository.save(post);
    }

    private void addForumComment(ForumPost post, UserAccount author, String content, int daysAgo) {
        ForumComment comment = new ForumComment();
        comment.setPost(post);
        comment.setAuthor(author);
        comment.setContent(content);
        comment.setApproved(true);
        comment.setCreatedAt(LocalDateTime.now().minusDays(daysAgo));
        forumCommentRepository.save(comment);
    }

    private void addFavorite(UserAccount user, Camera camera) {
        if (!favoriteRepository.existsByUserAndCamera(user, camera)) {
            UserFavorite favorite = new UserFavorite();
            favorite.setUser(user);
            favorite.setCamera(camera);
            favoriteRepository.save(favorite);
        }
    }

    private void upsertCamera(String brand, String model, String type, String photographyType, String sensor, String video, String price, Double resolution, Integer battery, String description) {
        Camera camera = cameraRepository.findByBrandIgnoreCaseAndModelIgnoreCase(brand, model).orElseGet(Camera::new);
        camera.setBrand(brand);
        camera.setModel(model);
        camera.setType(type);
        camera.setPhotographyType(photographyType);
        camera.setSensor(sensor);
        camera.setVideo(video);
        camera.setPrice(new BigDecimal(price));
        camera.setResolutionMp(resolution);
        camera.setBatteryShots(battery);
        camera.setDescription(description);
        if (camera.getRatingCount() == null || camera.getRatingCount() == 0) {
            camera.setAverageRating(0.0);
            camera.setRatingCount(0);
        }
        camera.setImageUrl(imageForBrand(brand));
        cameraRepository.save(camera);
    }

    private String imageForBrand(String brand) {
        String normalized = brand.trim().toLowerCase().replace(" ", "-");
        return switch (normalized) {
            case "canon" -> "/images/brands/canon.svg";
            case "nikon" -> "/images/brands/nikon.svg";
            case "sony" -> "/images/brands/sony.svg";
            case "fujifilm" -> "/images/brands/fujifilm.svg";
            case "panasonic" -> "/images/brands/panasonic.svg";
            case "olympus" -> "/images/brands/olympus.svg";
            case "om-system" -> "/images/brands/om-system.svg";
            case "leica" -> "/images/brands/leica.svg";
            case "pentax" -> "/images/brands/pentax.svg";
            case "hasselblad" -> "/images/brands/hasselblad.svg";
            case "gopro" -> "/images/brands/gopro.svg";
            case "dji" -> "/images/brands/dji.svg";
            case "ricoh" -> "/images/brands/ricoh.svg";
            default -> "/images/camera-placeholder.svg";
        };
    }

    private record DemoUsers(UserAccount admin, UserAccount ana, UserAccount mihai, UserAccount maria, UserAccount andrei, UserAccount vlad) {
    }
}
