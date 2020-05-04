open TW;
open Belt;

let formatDate = s => {
  let date = s->Js.Date.fromString->Js.Date.toLocaleDateString;
  let time = s->Js.Date.fromString->Js.Date.toLocaleTimeString;

  date ++ ", " ++ time;
};

let th = () =>
  [
    TextAlign(TextLeft),
    Padding(P2),
    Padding(Px6),
    BorderStyle(BorderSolid),
    BorderWidth(BorderB),
    BorderColor(BorderGray400),
  ]
  ->make;

let td = w =>
  [
    TextAlign(TextLeft),
    Padding(Py6),
    Padding(Px6),
    BorderStyle(BorderSolid),
    BorderWidth(BorderB),
    BorderColor(BorderGray200),
    Width(w),
  ]
  ->make;

type form = {
  name: option(string),
  email: option(string),
  number: option(string),
  surveyId: option(string),
};

let initialState = {name: None, email: None, number: None, surveyId: None};

open ReasonUrql.Hooks;

[@react.component]
let make = () => {
  let (page, setPage) = React.useState(_ => 1);

  let (form, setForm) = React.useState(_ => initialState);
  let (variables, setVariables) = React.useState(_ => initialState);

  let ({response, fetching}, _) =
    ResultsQuery.use(
      ~page,
      ~name=variables.name,
      ~email=variables.email,
      ~surveyId=variables.surveyId,
      ~number=variables.number,
    );

  <Layout>
    <div className={[Display(Flex), JustifyContent(JustifyBetween)]->make}>
      <Text className=TW.[FontSize(Text2xl), Margin(Mr4)]>
        {j|Wyniki|j}
      </Text>
    </div>
    <div
      className={
        [Display(Flex), AlignItems(ItemsCenter), Margin(My8)]->make
      }>
      <Input
        value={form.surveyId->Option.getWithDefault("")}
        onChange={v => setForm(s => {...s, surveyId: v})}
        placeholder={j|ID Ankiety|j}
        className=[Margin(Mr8)]
      />
      <Input
        value={form.name->Option.getWithDefault("")}
        onChange={v => setForm(s => {...s, name: v})}
        placeholder={j|Imię i nazwisko|j}
        className=[Margin(Mr8)]
      />
      <Input
        value={form.number->Option.getWithDefault("")}
        onChange={v => setForm(s => {...s, number: v})}
        placeholder={j|Numer albumu|j}
        className=[Margin(Mr8)]
      />
      <Input
        value={form.email->Option.getWithDefault("")}
        onChange={v => setForm(s => {...s, email: v})}
        placeholder={j|E-mail|j}
        className=[Margin(Mr8)]
      />
      <Button
        loading=fetching onClick={_ => {setVariables(_ => form) |> ignore}}>
        <Icons.Search />
        <Text color=`white className=[Margin(Ml4)]> {j|Szukaj|j} </Text>
      </Button>
    </div>
    {switch (response) {
     | Data(data) =>
       let solutions =
         data##solutions
         ->Option.map(e => e##entries)
         ->Option.getWithDefault([||])
         ->Array.map(f =>
             {
               "_id": f##_id,
               "name": f##name,
               "number": f##number,
               "email": f##email,
               "surveyId": f##surveyId,
             }
           );
       let total =
         data##solutions
         ->Option.map(s => s##entries->Array.length)
         ->Option.getWithDefault(0);

       <div>
         <table
           className={
             [
               Width(WFull),
               Margin(My8),
               BorderRadius(RoundedLg),
               BoxShadow(Shadow),
               Padding(P8),
             ]
             ->make
           }>
           <thead>
             <tr>
               <th className={th()}> <Text> {j|ID Ankiety|j} </Text> </th>
               <th className={th()}> <Text> {j|Uczestnik|j} </Text> </th>
               <th className={th()}> <Text> {j|Numer albumu|j} </Text> </th>
               <th className={th()}> <Text> {j|Email|j} </Text> </th>
             </tr>
           </thead>
           <tbody>
             {switch (total) {
              | 0 =>
                <tr>
                  <td colSpan=4>
                    <div
                      className={
                        [
                          Display(Flex),
                          AlignItems(ItemsCenter),
                          Padding(P8),
                        ]
                        ->make
                      }>
                      <div
                        className={
                          [
                            Display(InlineFlex),
                            Padding(P8),
                            BorderRadius(RoundedFull),
                            BoxShadow(ShadowLg),
                            BackgroundColor(BgBlue100),
                            Opacity(Opacity75),
                          ]
                          ->make
                        }>
                        <Icons.Slash size=48 color="#90cdf4" />
                      </div>
                      <div className={[Margin(Ml8)]->make}>
                        <div>
                          <Text className=TW.[FontSize(Text2xl)]>
                            {j|Brak wyników|j}
                          </Text>
                          <br />
                          <Text
                            className=[
                              FontSize(TextXl),
                              MaxWidth(MaxW2xl),
                              Display(Flex),
                            ]
                            color=`light>
                            {j|Wygląda na to że, w bazie nie ma wyników dla podanych kryteriów wyszukiwania, oznacza to że uzytkownik nie rozwiązał jeszcze ankiety|j}
                          </Text>
                        </div>
                      </div>
                    </div>
                  </td>
                </tr>
              | _ =>
                solutions
                ->Belt.Array.map(s =>
                    <tr key={s##_id}>
                      <td className={td(W1_6)}>
                        <Text> {s##surveyId} </Text>
                      </td>
                      <td className={td(W1_6)}> <Text> {s##name} </Text> </td>
                      <td className={td(W1_6)}>
                        <Text> {s##number} </Text>
                      </td>
                      <td className={td(W3_12)}>
                        <Text> {s##email} </Text>
                      </td>
                    </tr>
                  )
                ->React.array
              }}
           </tbody>
         </table>
         <div className={[Display(Flex), JustifyContent(JustifyEnd)]->make}>
           {Array.range(1, 1)
            ->Array.map(v =>
                <div
                  key={v->Js.Int.toString}
                  className={
                    [
                      Width(W12),
                      Height(H12),
                      BoxShadow(ShadowMd),
                      BorderRadius(RoundedLg),
                      Display(Flex),
                      AlignItems(ItemsCenter),
                      JustifyContent(JustifyCenter),
                      Margin(M1),
                      BackgroundColor(BgGray100),
                      Cursor(CursorPointer),
                    ]
                    ->make
                  }
                  onClick={_ => setPage(_ => v)}>
                  <Text> v->Js.Int.toString </Text>
                </div>
              )
            ->React.array}
         </div>
       </div>;

     | Fetching => <Text> {j|Wczytywanie|j} </Text>
     | NotFound => React.null
     | Error(_) => <Text> {j|Wystąpił nieoczekiwany błąd|j} </Text>
     }}
  </Layout>;
};